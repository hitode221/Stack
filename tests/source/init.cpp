#include "Stack.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>

SCENARIO("Stack push", "[push]") {
	stack<int> Stack;
	Stack.push(3);
	REQUIRE(Stack.pop() == 3);
}

SCENARIO("Stack pop", "[pop]") {
	stack<int> Stack;
	for (int i = 0; i < 10; i++) {
		Stack.push(i);
	}
	Stack.pop();
	REQUIRE(Stack.count() == 9);
}

SCENARIO("Stack count", "[count]"){
	stack<int> Stack;
	for (int i = 0; i < 10; i++) {
		Stack.push(i);
	}
	REQUIRE(Stack.count() == 10);
}
