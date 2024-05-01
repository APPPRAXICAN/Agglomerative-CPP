#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <limits>
#include <unordered_map>
#include <vector>
#include "tools.h"

dic labels;
_2DVector data {
					/*{1,1},
					{1.5,1.5},
					{5,5},
					{3,4},
					{4,4},
					{3,3.5}*/
{0.7, 3.2},
{2.45, 2.89},
{3.47, 1.12},
{5.23, 5.24},
{5.98, 6.23},
{7.778, 8.63},
//{8.97, 6.12}








};
int steps = 0;

void LabelsGenrator(_2DVector data) {
	for (int i = 0; i < data.size(); i++) {
		std::string label = "p" + std::to_string(i + 1);
		labels.insert({ i,label });
	}
}

double Euclidean(_1DVector p1, _1DVector p2) {
	return sqrt(std::pow((p1[0] - p2[0]), 2) + std::pow((p1[1] - p2[1]), 2));
}

_2DVector distanceMatrix(_2DVector data) {
	_2DVector DistanceMatrix;
	Initiate_2DVector<double>(DistanceMatrix, data.size());
	std::cout << "Distance : " << std::endl;
	int c = 0; 
	for (int i = 0; i < data.size(); i++) {
		_1DVector p1 = data[i]; 
		for (int j = i; j < data.size(); j++) {
			_1DVector p2 = data[j];
			std::cout << "d(" << i + 1 << "," << j + 1 << "): " << Euclidean(p1, p2) << std::endl;
			DistanceMatrix[i][j] = Euclidean(p1, p2);
			DistanceMatrix[j][i] = Euclidean(p1, p2);
		}
	}
	return DistanceMatrix;
}

int* indexOfMiniValue(_2DVector DM) {
	int* index = new int[2]; //row , col
	double min = INFINITY;
	for (int i = 0; i < DM.size(); i++) {
		for (int j = 0; j < DM[i].size(); j++) {
			if (DM[i][j] < min && DM[i][j] != 0) {
				min = DM[i][j];
				index[0] = i;
				index[1] = j;
			}
		}
	}
	line("_ _");
	std::cout << "minimum value = " << min;
	return index; 
}

map targetedRows(int* index, _2DVector DM) {
	map elements;
	elements["row1"] = DM[index[0]];
	elements["row2"] = DM[index[1]];
	return elements;
}

_1DVector clustering(int* index, _2DVector DM) {//index[0] => Host , index[1] => Guest
 	map elements = targetedRows(index, DM);
	_1DVector row1 = elements["row1"]; row1.erase(row1.begin() + index[1]);
	_1DVector row2 = elements["row2"]; row2.erase(row2.begin() + index[1]);
	_1DVector cluster;
	for (int i = 0; i < row1.size(); i++) {
		cluster.push_back(std::min(row1[i], row2[i]));
	}
	labels[index[0]] = labels[index[0]] + "," + labels[index[1]];
	labels.erase(index[1]);
	return cluster;
}

void shrink(_2DVector& DM ,int GuestElement) {
	DM.erase(DM.begin() + GuestElement);
	for (int i = 0; i < DM.size(); i++) {
		for (int j = 0; j < DM[i].size(); j++) {
			if (j == GuestElement) {
				DM[i].erase(DM[i].begin() + GuestElement);
			}
		}
	}
}

void insertCluster(_2DVector& DM, _1DVector cluster ,int HostElement ) {
	DM[HostElement] = cluster;
	for (int i = 0; i < DM.size(); i++) {
		for (int j = 0; j < DM.size(); j++) {
			if (j == HostElement && i != HostElement) {
				DM[i][j] = cluster[i];
			}
		}
	}
}

_2DVector Agglomerative(_2DVector & DM) {
	line("=+=");
	std::cout <<"                       steps(" << ++steps<<")";
	line("=+=");
	std::cout << "Current Clusters : ";
	line("---");
	testHashmap<int, std::string>(labels);
	int* miniIndex = indexOfMiniValue(DM);
	int HostElement = miniIndex[0]; 
	int GuestElement = miniIndex[1];
	_1DVector cluster = clustering(miniIndex, DM);
	shrink(DM, GuestElement);
	insertCluster(DM, cluster, HostElement);
	line("=*=");
	testMultiVector<double>(DM);
	line("-_-");
	if (DM.size() == 1) return DM;
	 return Agglomerative(DM);
}

int main(int argc, char** argv) {
	LabelsGenrator(data);
	line("=o=");
	_2DVector DM = distanceMatrix(data);
	line("=o=");
	std::cout << "Distance Matrix : " << std::endl;
	testMultiVector<double>(DM);
	line("-_-");
	Agglomerative(DM);
	testHashmap<int, std::string>(labels);
	return 0;
}