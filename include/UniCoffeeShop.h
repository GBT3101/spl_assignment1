/*
 * UniCoffeeShop.h
 *
 *  Created on: Nov 10, 2013
 *      Author: gbt
 */

#ifndef UNICOFFEESHOP_H_
#define UNICOFFEESHOP_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <limits>

using namespace std;

struct ingridient;
struct final_Prod;
struct sup;

vector<string> splitProducts(string record);
ingridient splitIngridient(string record);
vector<ingridient> findMIn(vector<ingridient> ingredients );
bool findName(string name, vector<ingridient> ingredients);
final_Prod calculateProd(vector<string> product, vector<ingridient> miningredients );
vector<sup> ordersFromSuppliers(vector<final_Prod> finalProducts);
bool supExistence(vector<sup> suppliers, string name);
bool ingExistence(vector<string> orderList, string name);
void master();


#endif /* UNICOFFEESHOP_H_ */
