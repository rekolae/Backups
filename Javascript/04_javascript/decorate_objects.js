function addPersonMethods(person) {
    person.greet = function (greetingString) {
        console.log(greetingString + ", my name is " + this.name);
    };

    person.compareAge = function (comparePerson) {
        if (this.age === comparePerson.age) {
            str = "My name is " + this.name + " and I'm equally young as " +
            comparePerson.name;

            console.log(str);
        }

        else if (this.age > comparePerson.age) {
            str = "My name is " + this.name + " and I'm older than " +
            comparePerson.name;

            console.log(str);
        }

        else if (this.age < comparePerson.age) {
            str = "My name is " + this.name + " and I'm younger than " +
            comparePerson.name;

            console.log(str);
        }
    };

    person.namesake = function (comparePerson) {
        if (this.name === comparePerson.name) {
            str = "We have the same name, " + comparePerson.name + " and I!";

            console.log(str);
        }

        else {
            str = "We have different names, " + comparePerson.name + " and I.";

            console.log(str);
        }
    };


    return person;
}
