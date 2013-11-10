/*
 * Main.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: Gil Yitzhak & Guy Ben-Moshe
 */

#include "../include/UniCoffeeShop.h"
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

/********************* Structures *********************/
/*
struct ingridient { // Represents an Ingredient
	string name; // name of ingredient
	string supplier; // name of the supplier of the ingredient
	double price; // the price of the ingredient

	ingridient() : name(""), supplier(""), price(0) {}
};

struct final_Prod { // represent the product with it's minimum ingredients needed, and it's minimal producing price
	double total; // the industrial price of the product
	string name; // name of the product
	vector<ingridient> minProdingredients; // a vector contains the minimal priced ingredients
	bool toTake; // boolean variable to determine if the product is fine to sell
	double finalPrice; // the final price of the product, *1.5 and +1nis

	final_Prod() : total(0), name(""), minProdingredients(0), toTake(), finalPrice(0) {}
};

struct sup { // represent a supplier
	string name; // name of the supplier
	vector<string> orderList; // the ingredients he sells

	sup() : name(""), orderList(0) {}
};



*/
/********************* FUnctions Declarations *********************/
/*
vector<string> splitProducts(string record);
ingridient splitIngridient(string record);
vector<ingridient> findMIn(vector<ingridient> ingredients );
bool findName(string name, vector<ingridient> ingredients);
final_Prod calculateProd(vector<string> product, vector<ingridient> miningredients );
vector<sup> ordersFromSuppliers(vector<final_Prod> finalProducts);
bool supExistence(vector<sup> suppliers, string name);
bool ingExistence(vector<string> orderList, string name);

*/
/********************* Main Function *********************/

int main(int argc, char **argv) {

	master();

	return 0;
}










