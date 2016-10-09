/*
 * Hello World from JavaScript
 */
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
try {
    flight.equipment.model                     // throw "TypeError"
} catch (e) {
    document.writeln(e);
}
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


/*
 * Prototype
 */

if (typeof Object.beget !== 'function') {
    Object.create = function(o) {
	var F = function(){};
	F.prototype = o;
	return new F();
    };
}

var another_stooge = Object.create(stooge);

another_stooge['first-name'] = 'Harry';
another_stooge['middle-name'] = 'Moses';
another_stooge.nickname = 'Moe';

stooge.profession = 'actor';
another_stooge.profession  // 'actor'


/*
 * Reflection
 */

typeof flight.number   // 'number'
typeof flight.status   // 'string'
typeof flight.arrival  // 'object'
typeof flight.manifest // 'undefined'

// prototype's attributes
typeof flight.toString    // 'function'
typeof flight.constructor // 'function'

// only object own attributes
flight.hasOwnProperty('number')       // true
flight.hasOwnProperty('constructor')  // false


/*
 * Enumeration
 */

// out of order for-each
var name;
for (name in another_stooge) {
    if (typeof another_stooge[name] !== 'function') {
	document.writeln(name + ': ' + another_stooge[name]);
    }
}

// in order for-each
var i;
var properties = [
    'first-name',
    'middle-name',
    'last-name',
    'profession'
];
for (i = 0; i < properties.length; i++) {
    document.writeln(properties[i] + ': ' + another_stooge[properties[i]]);
}


/*
 * Delete
 */

another_stooge.nickname = 'Moe';  // 'Moe'
delete another_stooge.nickname;   // expose prototype object's property
another_stooge.nickname           // 'Curly'


/*
 * Global Abatement
 */

var MYAPP = {};

MYAPP.stooge = {
    "first-name": "Jerome",
    "last-name": "Howard"
};

MYAPP.flight = {
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
 * Function Objects
 */

Object.prototype
Function.prototype


/*
 * Function Literal
 *
 * anonymous
 * closure
 */

var add = function(a, b) {
    return a + b;
};


/*
 * Invocation
 *
 * this
 * arguments
 */


/*
 * The Method Invocation Pattern
 */

var myObject = {
    value: 0,
    increment: function(inc) {
	this.value += typeof inc == 'number' ? inc : 1;
    }
};

myObject.increment();
document.writeln(myObject.value);  // 1

myObject.increment(2);
document.writeln(myObject.value);  // 3

/*
 * The Function Invocation Pattern
 */

var sum = add(3, 4);  // sum's value is 7

myObject.double = function() {
    var that = this;

    var helper = function() {
	that.value = add(that.value, that.value);
    };
    helper();
}

myObject.double();
document.writeln(myObject.value);

/*
 * The Constructor Invocation Pattern
 */

var Quo = function(string) {
    this.status = string;
};

Quo.prototype.get_status = function() {
    return this.status;
};

var myQuo = new Quo("confused");
document.writeln(myQuo.get_status());  // "confused"

/*
 * The Apply Invocation Pattern
 */

var array = [3, 4];
var sum = add.apply(null, array);  // sum's value is 7

var statusObject = {
    status: 'A-OK'
};

var status = Quo.prototype.get_status.apply(statusObject);


/*
 * Arguments
 */

var sum = function() {
    var i, sum = 0;
    for (i = 0; i < arguments.length; i++) {
	sum += arguments[i];
    }
    return sum;
};

document.writeln(sum(4, 8, 15, 16, 23, 42));  // 108


/*
 * Return
 */

// return undefined
// return this


/*
 * Exceptions
 */

var add = function(a, b) {
    if (typeof a !== 'number' || typeof b !== 'number') {
	throw {
	    name: 'TypeError',
	    message: 'add needs numbers'
	};
    }
    return a + b;
};

var try_it = function() {
    try {
	add("seven");
    } catch (e) {
	document.writeln(e.name + ': ' + e.message);
    }
};

try_it();


/*
 * Argument Types
 */

Function.prototype.method = function(name, func) {
    this.prototype[name] = func;
    return this;
};

Number.method('integer', function(){
    return Math[this < 0 ? 'ceil' : 'floor'](this);
});
document.writeln((-10 / 3).integer());  // -3

String.method('trim', function(){
    return this.replace(/^\s+|\s+$/g, '');
});
document.writeln('"' + "    neat    ".trim() + '"');


/*
 * Recursion
 */

var hanoi = function(disc, src, aux, dst) {
    if (disc > 0) {
	hanoi(disc - 1, src, dst, aux);
	document.writeln('Move disc ' + disc + ' from ' + src + ' to ' + dst);
	hanoi(disc - 1, aux, src, dst);
    }
};

hanoi(3, 'Src', 'Aux', 'Dst');

var factorial = function factorial(i, a) {
    a = a || 1;
    if (i < 2)
	return a;
    return factorial(i - 1, a * i);
};

document.writeln(factorial(4));  // 24


/*
 * Closure
 */

var myObject = (function(){
    var value = 0;

    return {
	increment: function(inc) {
	    value += typeof inc === 'number' ? inc : 1;
	},
	getValue: function() {
	    return value;
	}
    };
}());


/*
 * Module
 */

String.method('deentityify', function(){
    var entity = {
	quot: '"',
	lt: '<',
	gt: '>'
    };

    return function() {
	return this.replace(/&([^&;]+);/g, function(a, b) {
	    var r = entity[b];
	    return typeof r === 'string' ? r : a;
	});
    };
}());


/*
 * Curry
 */

Function.method('curry', function() {
    var slice = Array.prototype.slice,
	args = slice.apply(arguments),
	that = this;
    return function() {
	return that.apply(null, args.concat(slice.apply(arguments)));
    };
});
