/*
 * Function used to define new method.
 */
Function.prototype.method = function(name, func) {
    this.prototype[name] = func;
    return this;
}

document.writeln('Hello, world!');


// Object literal

var empty_object = {};

var stooge = {
    "first-name": "Jerome",
    "last-name": "Howard"
};

var flight = {
    airline: "Oceanic",
    number: 815,
    departure: {
	IATA: "SYD",
	time: "2004-09-22 14:55",
	city: "Sydney"
    },
    arrival: {
	IATA: "LAX",
	time: "2004-09-23 10:42",
	city: "Los Angeles"
    }
};
