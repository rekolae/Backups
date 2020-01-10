# BWA/TIETA12 coursework assignment

In the assignment, we gamify multi-choice questionnaire.
The assignment consists of three parts: the game, management view, and testing/documentation.

1. game - some mechanism for selecting the right answers

2. management implies CRUD operations: questions can be created, queried, modified, and deleted.

3. test your modifications, that is game and management view in particular, other tests can be implemented as well.

In the beginning of December, we will meet all the groups to check that each
group has some idea how to proceed.
In addition, we promote MIT licensing:
if you grant the license, your game may be integrated in the LukioPlussa project;
the project is funded by the Ministry of Education. Its aim is to provide free learning material
for high-school students, especially for the domains of mathematics and computer science.

### The project structure

```
.
├── app.js                  --> express app
├── index.js                --> bwa app
├── package.json            --> app info and dependencies
├── middleware              --> all kinds of middleware used by the express app
├── controllers             --> controllers (handle e.g. routing)
│   ├── game.js             --> questionnaire game
│   ├── games.js            --> prints list of games
│   ├── hello.js            --> the same as "minimal viable grader"
│   ├── management.js       --> management functions
│   └── users.js            --> user operations
├── models                  --> models that reflect the db schemes and take care of storing data
│   ├── ourGame.js          --> grader for questionnaire game
│   └── ...                 --> ...
├── public                  --> location for public (static) files
│   ├── img                 --> for images
│   ├── js                  --> for javascript
│   ├── css                 --> for styles
│   └── resources           --> for static files
├── routes                  --> a dir for router modules
│   ├── game.js             --> /game router (also handles hello.js)
│   ├── management.js       --> /management router
│   └── users.js            --> /users router
├── views                   --> views - visible parts
│   ├── error.hbs           --> error view
│   ├── ourGame.hbs         --> game view
│   ├── ourGame-graded.hbs  --> graded game view
│   ├── hello.hbs           --> main view - "minimal viable grader"
│   ├── layouts             --> layouts - handlebar concept
│   │   └── default.hbs      --> default layout view, "template" to be rendered
│   ├── management          --> layouts for management views
│   └── partials            --> smaller handlebar components to be included in views
└── test                    --> tests
    ├── assignment          --> our tests. Read more at Tests and documentation
    ├── integration         --> integration tests
    └── models              --> unit tests for models

```



- controllers
    - game.js: questionnaire game. Reads questions from database and renders the game
    - games.js: Reads all of the questionnaires from the database and renders the game list
    - management.js: Handles all of the crud operations for the questionnaires
- models
    - ourGame.js: grader for questionnaire game
- public
    - img
        - favicon.ico: Favicon for the site
    - js
        - createQuestionnaire.js: Scripts for creating questionnaires
        - managementView.js: Scripts for management view
        - modifyQuestionnaire.js: Scripts for modifying questionnaires
    - resources
        - empty_questionnaire.json: Example questionnaire frame that can be downloaded by the user
 - routes
    - game.js:
    - management.js: Handles all of the routing between different management pages
- test
    - assignment
        - Management.test.js: Tests Creating, Reading, Updating and Deliting questionaries.
        - Ourgame.test.js: Tests our games. Checks that games open and included forms and buttons
        - Games.test.js: Tests games page (Page that includes links to our games). Checks that page opens and includes correct links to our games.
- views
    - management
        - createQuestionnaire.hbs: Template for rendering the page for creating questionnaires
        - managementView.hbs: Template for rendering "main" management view
        - modifyQuestionnaire.hbs: Template for rendering the page for modifying questionnaires
    - partials
        - createQuestionnaire_scripts.hbs: Template that includes scripts
        - deleteModal.hbs: Template for delete dialog
        - managementView_scripts.hbs: Template that includes other scripts
        - modifyQuestionnaire_scripts.hbs: Template that includes some other scripts
        - uploadModal.hbs: Template for file upload dialog
    - gameList.hbs: Template used to display all of the questionnaires in the database
    - ...
- .jshintrc: Config for jshint


## Game

Game list can be found at /games
Games are found at /games/<gameId>  (the gameId can be anything as it is fetched from the database)
Hello game can be found at localhost:3000/

Our game is a simple multiple choice questionnaire. Questionnaire can have any
number of questions and questions can have any number options as long as there
is at least one question and each question has at least two options. Each correct
option is worth a one point. User just selects some of the options and then pushes
the grade button to receive a grade. Grade is shown on a feedback page which shows
all of the questions and your answers. If users gets all of the points from a question
it is marked in green. If the user has not selected any options or has selected some of
correct answers not any wrong answers the question is colored in yellow. If the users
has selected at least a one incorrect answer they will receive zero points and the
question is marked in red. Hints are shown after each selected options if there are
any to show. User can change their selections on the feedback page and send it for
grading again without going back to original questionnaire page.

## Management view

Management view consists of three different views:
    - Primary view that has all of the questionnaires listed.
        - Real time search function
        - Add questionnaire button
        - Modify and delete buttons for each questionnaire
    - View for creating questionnaires
        - Questions can be added by pressing a buttons
        - Choices can be added by pressing a button
        - Questionnaires can be also uploaded as a JSON
        - Example questionnaire JSON can be downloaded
    - View for modifying questionnaires
        - Questions and choices can be deleted one-by-once
        - Existing choices and questions can be modified
        - Questionnaire title and submissions can be modified
        - New questions can be added

These views implement all of the CRUD operations. The views are created with the
help of .hbs files and some of the page functinality is implemented using jQuery.

## Tests and documentation

Our tests are located in test/assignment. We have following three test files:

**Management.test.js**: Tests creating, reading, updating and deleting questionaries.
**Games.test.js**: Tests games page. Checks that page opens and it includes links to our games.
**Ourgame.test.js**: Tests our games. Checks that each game page opens and includes form and grading button.

Our tests use database. If we run our test with other test using "npm test", database cannot be found (Meaning questionaries seem empty). 
**npm test DOES NOT WORK**. Because of this, tests should be run seperately.

We run our tests with following command: *npx mocha test/assignment*.
Run course tests with commands: *npx mocha test/integration* and *npx mocha test/models*

Sometimes some of our tests are not running as expected. It seems like games.test.js and ourgame.test.js that use zombie are
not able to always open the page correctly and because of this forms and buttons do not exist (In manual testing this does not happen).
At some point, few course side tests started failing. 
We are not able to reproduce these course side failing while using our game, so we ignored them.

We have tested our game manually. Our games should start and grading should work. You also should be able to create, read, update and delete games.

## Security concerns

Users can insert new data to database so there is a danger of XSS when that data is render in the game.
This is prevented by XSS filtering all of data before it is shown on the page.

Data parsed from forms in the management view is sanitized using express sanitizer, but there are still
some ways to circumvent these security measures.

There is always a possibility that a teacher or an admin gets their password stolen, but against that
we can't really do anything.

---

## Installation

1. Install `nodejs` and `npm`, if not already installed.

2. Execute in the root, in the same place, where _package.json_-file is):

    ```
    npm install
    ```

3. **Copy** `.env.dist` in the root with the name `.env` (note the dot in the beginning of the file)

    ```
    cp -i .env.dist .env
    ```

    **Obs: If `.env`-file already exists, do not overwrite it!**

    **Note: Do not save `.env` file to the git repository - it contains sensitive data!**

    **Note: Do not modify `.env.dist` file. It is a model to be copied as .env, it neither must not contain any sensitive data!**

    Modify `.env` file and set the needed environment variables.

    In the real production environment, passwords need to be
    long and complex. Actually, after setting them, one does
    not need to memorize them or type them manually.

4. `Vagrantfile` is provided. It defines how the vagrant
   environment is set up, commands to be run:

    `vagrant up` //sets up the environment
    `vagrant ssh` //moves a user inside vagrant

    Inside vagrant, go to the directory `/bwa` and start the app:
    `npm start`

5. As an other alternative, `Dockerfile` is provided as well.
   Then, docker and docker-compile must be installed.
   In the root, give:

    ```
    docker-compose build && docker-compose up
    ```

    or

    ```
    docker-compose up --build
    ```

    The build phase should be needed only once. Later on you should omit the build phase and simply run:

    ```
    docker-compose up
    ```

    The container is started in the terminal and you can read what is written to console.log. The container is stopped with `Ctrl + C`.


    Sometimes, if you need to rebuild the whole docker container from the very beginning,
    it can be done with the following command:

    ```
    docker-compose build --no-cache --force-rm && docker-compose up
    ```

6. Docker container starts _bwa_ server and listens `http://localhost:3000/`

7) Docker container is stopped in the root dir with a command:

    ```
    docker-compose down
    ```

## Coding conventions

Project uses _express_ web app framework (https://expressjs.com/).
The application starts from `index.js` that in turn calls other modules.  
The actual _express_ application is created and configured in `app.js` and
routes in `router.js`.

The application complies with the _MVC_ model, where each route has
a corresponding _controller_ in the dir of `controllers`.
Controllers, in turn, use the models for getting and storing data.
The models centralize the operations of e.g. validation, sanitation
and storing of data (i.e., _business logic_) to one location.
Having such a structure also enables more standard testing.

As a _view_ component, the app uses _express-handlebars_;
actual views are put in the dir named `views`. It has two subdirectories:
`layouts` and `partials`.
`layouts` are whole pages, whereas `partials` are reusable smaller
snippets put in the `layouts` or other views. Views, layouts, and partials
use _handlebars_ syntax, and their extension is `.hbs`.
More information about _handlebars_ syntax can be found in: http://handlebarsjs.com/

Files such as images, _CSS_ styles, and clientside JavaScripts are under the `public` directory. When the app is run in a browser, the files are located under the`/`path, at the root of the server, so the views must refer to them using the absolute path. (For example, `<link rel =" stylesheet "href =" / css / style.css ">`) ** Note that `public` is not part of this path. **

The _mocha_ and _chai_ modules are used for testing and the tests can be found under the `test` directory.

##About coding policies

The project code aims to follow a consistent coding conventions
ensured by using the _eslint_ code validation tool. The primary purpose of the tool is to ensure that the project code follows more or less the generally accepted style of appropriate conventions, and that the code avoids known vulnerabilities and / or risky coding practices. In addition, the tool aims to standardize the appearance of code of all programmers involved in the project so that all code is easy to read and maintainable for non-original coders as well.

English is recommended for naming functions and variables and commenting on code. Git commit messages should also be written in English, but this is neither required nor monitored.

##Code style

The _eslint_ tool used is configured to require certain stylistic considerations that can reasonably be considered as opinion issues and may not necessarily be true or false. The intention is not to initiate any debate on the subject or upset anyone's mind, but to strive for uniformity in the appearance of the code, with no other motives.

This project follows the following coding styles:

-   indents with 4 spaces
-   the code block starting bracket `{` is in the same line as the block starting the function, clause or loop
-   the block terminating bracket `}` in the code block is always on its own line, except in cases where the whole block is on a single line
-   the _camelCase_ style is recommended for naming functions and variables
-   the variables should not be defined by using the `var` keyword, but the variables and constants are defined using the`let` and `const` keywords
-   each line of code ends with a semicolon `;`

You can check the style of your code by command:

`` ` npm run lint `` `

_eslint_ can also correct some code errors and style violations automatically, but you shouldn't rely on this blindly. You can do this explicitly with the command:

`` ` npm run lint:fix `` `

Naturally, it is easier to set up a code editor to monitor and correct the style during coding.

The project root directory contains the VSCode Editor configuration folder, where the appropriate settings are available for the editor. In addition, it contains plugin recommendations that VSCode will offer to install if the user so wishes. In addition, the project includes the _.editorconfig_ file, which allows you to easily import some of your settings to a number of other editors.
