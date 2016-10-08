/*
 * Function used to define new method.
 */
Function.prototype.method = function(name, func) {
    this.prototype[name] = func;
    return this;
}

document.writeln('Hello, world!');


/*
 * Object Literals
 */

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


/*
 * Retrieval
 */

stooge["first-name"]  // "Jerome"
flight.departure.IATA // "SYD"

stooge["middle-name"] // undefined
flight.status         // undefined
stooge["FIRST-NAME"]  // undefined

// default value using '||'
var middle = stooge["middle-name"] || "(none)";
var status = flight.status || "unknown";

// undefined throws TypeError
flight.equipment                           // undefined
flight.equipment.model                     // throw "TypeError"
flight.equipment && flight.equipment.model // undefined


/*
 * Update
 */

stooge["first-name"] = "Jerome";
stooge["middle-name"] = "Lester";
stooge.nickname = "Curly";
flight.equipment = {
    model: 'Boeing 777'
};
flight.status = 'Overdue';


/*
 * Reference
 */

var x = stooge;
x.nickname = 'Curly';
var nick = stooge.nickname;

var a = {}, b = {}, c = {};
a = b = c = {};
