/*
 * UniCoffeeShop.cpp
 *
 *  Created on: Nov 3, 2013
 *      Author: yitzhakg
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <limits>
#include "../include/UniCoffeeShop.h"

using namespace std;

/********************* Structures *********************/

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

/********************* Functions *********************/

void master(){
	ifstream productsInput;
		vector< vector<string> > products; // Vector for the raw products
		vector<string> tmp;

		productsInput.open("Products.conf"); // Read from the "Products" file.

		while (!productsInput.eof()) { // creates the products vectors
			string src;
			getline(productsInput, src);
			tmp = splitProducts(src);
			products.push_back(tmp);
		}

		productsInput.close(); // End reading from "Products".

		ifstream suppliersInput;
		vector<ingridient> ingredients; // vector for the ingredients

		suppliersInput.open("Suppliers.conf"); // Start reading from the "SUppliers" file.
		while (!suppliersInput.eof()) { // creates the ingredients vector
			string record;
			ingridient temp;
			getline(suppliersInput,record);
			ingredients.push_back(splitIngridient(record));
		}

		suppliersInput.close(); // End reading from "Suppliers"

		vector<ingridient> miningredients = findMIn(ingredients); // the vector of the minimal priced ingredients
		vector<final_Prod> finalProducts; // the vector of the final products

		for (unsigned int i=0; i<products.size(); i++)
			finalProducts.push_back(calculateProd(products[i], miningredients)); // Calculating the products and ingridients to create the final product

		ofstream outMenu;
		outMenu.open("Menu.out"); // Start writing to the "Menu" file.

		for (unsigned int k=0; k<finalProducts.size(); k++) {
			if(finalProducts[k].toTake) { // Write only those who has the final price less than 5
				outMenu << finalProducts[k].name << "," << finalProducts[k].finalPrice << endl;
			}
		}

		outMenu.close(); // End writing to the file "Menu".

		ofstream outShoppingList;
		outShoppingList.open("ShoppingList.out"); // Start writing to "ShoppingList" file.

		vector<sup> suppliers = ordersFromSuppliers(finalProducts); // Vector to contain the suppliers.

		for (unsigned int i=0 ; i<suppliers.size(); i++){
			outShoppingList << suppliers[i].name; // First, print the supplier's name.
			for (unsigned int j=0; j<suppliers[i].orderList.size()-1; j++)
				outShoppingList << "," << suppliers[i].orderList[j];
			outShoppingList << "," << suppliers[i].orderList[suppliers[i].orderList.size()-1] << endl;
		}

		outShoppingList.close(); // End writing to the "ShoppingList" file.
}

/**
 * The splitProduct Function gets a string and makes a vector contain the product's name and it's ingredients.
 */
vector<string> splitProducts(string record){
	vector<string> ans;
	string tmp;
	for (unsigned int i=0; i<record.length(); i++){ // split the ','
		if(record.at(i) == ','){
			ans.push_back(tmp);
			tmp="";
		}
		else{
			tmp+=record.at(i);
		}
	}
	ans.push_back(tmp);
	return ans;
}

/**
 * the splitIngredient Function gets a string and creates an "Ingredient" Object, contains the name, supplier, and price.
 */
ingridient splitIngridient(string record){
	ingridient ans;
	string tmp;
	int room;
	for(unsigned int i=0; i<record.length(); i++){
		if(record.at(i)==',' || i == record.length()-1){
			if(room==0) // the supplier's name
				ans.supplier = tmp;
			if(room==1) // the ingredient's name
				ans.name = tmp;
			if (room==2){ // the price
				tmp += record.at(i);
				ans.price = atof(tmp.c_str());
			}
			room++;
			tmp = "";
		}
		else
			tmp += record.at(i);
	}
	return ans;
}

/**
 * The findMin Function takes the full Ingredients and output a minimum vector contains all the INgredients and it's minimum price.
 */
vector<ingridient> findMIn(vector<ingridient> ingredients ){
	vector<ingridient> ans;
	ingridient tmp;
	for(unsigned int i=0; i<ingredients.size(); i++){
		tmp = ingredients[i];
		if(!(findName(tmp.name, ans))) // the ingredient's already there, there is no need to add it
		{
			for(unsigned int j=i; j<ingredients.size(); j++){ // find the minimum
				if (tmp.name == ingredients[j].name && ingredients[j].price < tmp.price){
					tmp = ingredients[j];
				}
			}
			ans.push_back(tmp); // push the minimum to the final vector
		}
	}
	return ans;
}

/**
 * the findName function takes an ingredient's name and checks if it's in the vector.
 */
bool findName(string name, vector<ingridient> ingredients){
	bool ans=false;
	for(unsigned int i=0; i<ingredients.size(); i++){
		if(name==ingredients[i].name)
			ans = true; // the ingredient is already in the function, return true
	}
	return ans;
}

/**
 * the calculateProd function gets the product's vector and it's miningredients, and create an integrated Object called the final product.
 */
final_Prod calculateProd(vector<string> product, vector<ingridient> miningredients) {


	final_Prod ans;
	ans.name = product[0];
	for (unsigned int i=1; i<product.size(); i++) {
		string temp = product[i];
		for (unsigned int j=0; j<miningredients.size(); j++)
			if (miningredients[j].name == temp){
				ans.minProdingredients.push_back(miningredients[j]);
			}
	}
	for (unsigned int i=0; i<ans.minProdingredients.size(); i++) {
		ans.total += ans.minProdingredients[i].price;

	}
	ans.finalPrice = (ans.total+1)*1.5; // calculate the final price
	ans.toTake = ans.finalPrice<=5; // determine if the product is good to take
	return ans;
}

/**
 * the ordersFRomSuppliers Function takes the final products vector and determine what suppliers we need and what ingredients from them and created a vector for it.
 */
vector<sup> ordersFromSuppliers(vector<final_Prod> finalProducts) {
	vector<sup> suppliers;
	for (unsigned int i=0; i<finalProducts.size(); i++) {
		if (finalProducts[i].toTake) {
			for (unsigned int j=0; j<finalProducts[i].minProdingredients.size(); j++) {
				string tempSupName = finalProducts[i].minProdingredients[j].supplier;
				if (!(supExistence(suppliers,tempSupName))) {
					sup tempSup;
					tempSup.name = tempSupName;
					tempSup.orderList.push_back(finalProducts[i].minProdingredients[j].name);
					suppliers.push_back(tempSup);
				}
				else {
					bool foundSup = false;
					for (unsigned int k=0; (k<suppliers.size()) && (foundSup==false); k++) {
						if (suppliers[k].name == tempSupName) {
							if (!(ingExistence(suppliers[k].orderList,finalProducts[i].minProdingredients[j].name)))
								suppliers[k].orderList.push_back(finalProducts[i].minProdingredients[j].name);
							foundSup=true;
						}
					}
				}
			}
		}
	}
	return suppliers;
}

/**
 * the supExistence Function finds out if the supplier is already in the suppliers vector
 */
bool supExistence(vector<sup> suppliers, string name) {
	bool ans = false;
	for (unsigned int i=0; (i<suppliers.size()) && (ans == false); i++)
		if (suppliers[i].name == name)
			ans = true;
	return ans;
}

/**
 * the ingExistence FUnction finds out if the ingredient is already in the vector.
 */
bool ingExistence(vector<string> orderList, string name) {
	bool ans = false;
	for (unsigned int i=0; (i<orderList.size()) && (ans == false); i++)
		if (orderList[i]==name)
			ans = true;
	return ans;
}
