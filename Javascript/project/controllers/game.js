'use strict';

const Game = require('../models/ourGame');
const xss_filter = require("xss-filters");
let questionnaireModel = require('../models/questionnaire');

module.exports = {
    /**
    * Prints exercise page
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async showExercise(request, response) {
        //Fetch data from database
        const doc = await questionnaireModel.findById(request.params.id).exec();
        try {
            if(doc != null){
                renderGame(response, doc);
            }
            else{
                response.render('error',{
                    error : {
                        status : 500,
                    },
                    message: 'Error while reading questions from database',
                });
            }
        }
        catch (err) {
            response.render('error',{
                error : {
                    status : 500,
                },
                message: 'Error while rendering questions',
            });
        }
    },


    /**
    * gradeExercise returns a grade for answer
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */

    async gradeExercise(request, response) {

        let correctAnswers = [];
        let maxPointsArray = [];
        let maxPoints = 0;
        let feedback;
        let values;

        const doc = await questionnaireModel.findById(request.params.id).exec();
        try{

            for(let question of doc.questions){
                let optionIndex = 0;
                let localCorrectAnswers = [];

                for(let option of question.options){
                    //collect correct answers
                    if(option.correctness.toString() === 'true'){
                        localCorrectAnswers.push(optionIndex);
                    }
                    optionIndex++;
                }
                correctAnswers.push(localCorrectAnswers);
                //add each questions max points in to an array and accumulate overall maxpoints
                maxPointsArray.push(question.maxPoints);
                maxPoints += question.maxPoints;
            }
            //Grade exercise
            values = await Game.grade(request,correctAnswers, maxPointsArray);
            //Give feedback
            feedback = await makeFeedback(doc, values);
        }
        catch(err){
            values = [-1,'Error while reading questions from database'];
        }
    renderFeedback(request, response, values,maxPoints, feedback);
    }
};



/**
* Makes HTNL page with questions
* @param {Object} response is express response object
* @param {Object} data contains question data
*/
function renderGame(response, data){

    let questionForm = '';
    let questionIndex = 0;

    //Go through all of the questions
    for(let question of data.questions){

        // add questions and points
        let optionForm =
        `
        <div class="form-group">
            <p style="float:left;display:inline">${(questionIndex+1)}. ${question.title}</p>
            <p style="float:right;display:inline">${question.maxPoints}p</p>
        <div style="clear:both">
        <form method="POST">
        `;

        let index = 0;
        //make unique name for each question button group
        let name =  questionIndex.toString();
        //Add options
        for (let option of question.options){
            //make unique id for each option
            let id = questionIndex.toString() + index.toString();

            optionForm +=
            `<label class="block">
                <input type="checkbox" name="${name}" id="${id}" value="${index}"> ${xss_filter.inHTMLData(option.option)}
            </label><br>
            `;

            index++;
        }
        questionIndex++;
        optionForm += '</div></div><hr>';
        questionForm += optionForm;
    }

    // Render the page
    response.render('ourGame',{
        options: questionForm,
        title : data.title
    });
}



/**
* Makes feedback for user based on their answers
* @param {Object} values contains data from grader
* @param {Object} data contains question data
*/
function makeFeedback(data, values){

    let pointsArray = values[0];
    let answers = values[2];

    try{
        let feedback = '<div class="form-group">';
        let usersAnswers = values[2];
        let questionIndex = 0;

        //Go through all questions
        for(let question of data.questions){
            let index = 0;
            let name =  questionIndex.toString();

            //Set right color for question div
            if(pointsArray[questionIndex] === question.maxPoints){
                /*
                feedback += '<div class="alert alert-success"><p style="float:left;display:inline">'
                +(questionIndex+1)+'. '+ question.title +'</p>';

                feedback += '<p style="float:right;display:inline">'+pointsArray[questionIndex]
                +'/'+question.maxPoints+'p'+'</p>';
                */


                feedback +=
                `
                <div class="alert alert-success">
                    <p style="float:left;display:inline">${(questionIndex+1)}. ${question.title}</p>
                    <p style="float:right;display:inline">${pointsArray[questionIndex]}/${question.maxPoints}p</p>
                `;
            }

            else if (pointsArray[questionIndex] === 0){
                /*
                feedback += '<div class="alert alert-danger"><p style="float:left;display:inline">'
                +(questionIndex+1)+'. '+ question.title +'</p>';

                feedback += '<p style="float:right;display:inline">0/'+question.maxPoints+'p'+'</p>';
                */

                feedback +=
                `
                <div class="alert alert-danger">
                    <p style="float:left;display:inline">${(questionIndex+1)}. ${question.title}</p>
                    <p style="float:right;display:inline">0/${question.maxPoints}p</p>
                `;
            }

            else{
                let points = 0;
                /*
                feedback += '<div class="alert alert-warning"><p style="float:left;display:inline">'
                +(questionIndex+1)+'. '+ question.title +'</p>';
                */

                if(pointsArray[questionIndex] != undefined){
                    points = pointsArray[questionIndex];
                }
                /*
                feedback += '<p style="float:right;display:inline">'+points+'/'+question.maxPoints+'p'+'</p>';
                */
                feedback +=
                `
                <div class="alert alert-warning">
                    <p style="float:left;display:inline">${(questionIndex+1)}. ${question.title}</p>
                    <p style="float:right;display:inline">${points}/${question.maxPoints}p</p>
                `;

            }
            feedback += '<div style="clear:both"><p>Your answers: </p>';

            // Go through all options
            for(let option of question.options){

                //make unique id for each option
                let id = questionIndex.toString() + index.toString();
                let checked = '';

                if(answers[questionIndex] != undefined){
                    if(answers[questionIndex].includes(index.toString())){
                        checked = 'checked';
                    }
                }

                // Add options and hints
                feedback += '<label class="block"><input type="checkbox" name="'+ name+'" id="'+
                id +'" value="'+index+'"'+checked+'>' +' '+
                xss_filter.inHTMLData(option.option);

                if(option.hint != undefined && checked != ''){
                    feedback += ' Hint: ' + option.hint;
                }

                feedback += '</label><br>';
                index++;
            }

            feedback += '</div></div><hr>';
            questionIndex++;
        }
        feedback += '</div>';

        return feedback;

    }

    //Error while making feedback
    catch(err){
        console.log(err);
        let feedback = "Could not create feedback";
        return feedback;

    }
}



/**
* Renders feedback page
* @param {Object} request is express request object
* @param {Object} response is express response object
* @param {Object} values contains data from grader
* @param {Arrya} data max points for the exercise
* @param {String} request feedback for the user
*/
function renderFeedback(request, response, values, maxPoints, feedback){

    let err = values[1];
    let status = 'graded';
    let error = 0;
    let points = 0;

    try{
        // Add points together
        points = values[0].reduce((a, b) => a + b, 0);
    }
    catch(e){
        points = -1;
        err = 'Error: Could not grade exercise';
    }

    //Error happened during grading
    if(points === -1){
        status = 'error';
        points = 0;
        error = 1;
    }

    response.render('ourGame-graded', {
        points: points,
        maxPoints: maxPoints,
        status: status,
        description: 'Grader for ourGame',
        title: 'A+ greetings',
        error : error,
        message : err,
        feedback : feedback,
        link : `href="/games/id/${request.params.id}"`
    });
}
