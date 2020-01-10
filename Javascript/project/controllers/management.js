'use strict';

const Questionnaire = require('../models/questionnaire');

module.exports = {
    /**
    * Gets all questionnaires from the database and shows management view
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async showManagementOptions(request, response) {
        Questionnaire.find({}, function(err, questionnaires) {
            if (err) {
                response.render('error', {
                    error : {
                        status : 500
                    },
                    message: 'Error while reading questionnaires from database'
                });
            } else {
                response.render('management/managementView', questionnaires);
            }
        });
    },

    /**
    * Shows questionnaire creation view
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async createQuestionnaire(request, response) {
        response.render('management/createQuestionnaire');
    },

    /**
    * Parses submitted questionnaire
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async parseQuestionnaire(request, response) {

        // Handle submitted file
        if (request.params.type === "json") {
            if (request.files == null) {
                request.flash('errorMessage', 'No file was uploaded');
                response.redirect('/management/create');
            }

            else {
                let questionnaire = JSON.parse(request.files.questionnaire.data.toString());

                // Try to create a questionnaire from the JSON
                try {
                    await Questionnaire.create(questionnaire);
                    request.flash('successMessage', 'JSON submitted successfully');
                    response.redirect('/management/create');
                }

                catch (err) {
                    response.render('error', {
                        error : {
                            status : 500
                        },
                        message: err
                    });
                }
            }
        }

        // Handle submitted form
        else if (request.params.type === "form") {

            let questionnaire = {
                "title" : "",
                "submissions" : "",
                "questions" : []
            };

            let obj = request.body;

            questionnaire.title = obj.questionnaireTitle;
            questionnaire.submissions = obj.submissions;

            delete obj.questionnaireTitle;
            delete obj.submissions;

            let question_container = {};

            // First create the questions into the JSON
            for (let key in obj) {
                if (obj.hasOwnProperty(key)) {
                    let key_split = key.split(".");
                    if (key_split.length == 2 && key_split[1] == "title") {
                        question_container.title = obj[key];
                        delete obj[key];
                    }

                    else if (key_split.length == 2 && key_split[1] == "maxPoints") {
                        question_container.maxPoints = obj[key];
                        question_container.options = [];
                        questionnaire.questions.push(question_container);

                        delete obj[key];
                        question_container = {};
                    }
                }
            }

            let choice_container = {};

            // Then handle the questions
            for (let key in obj) {
                if (obj.hasOwnProperty(key)) {
                    let key_split = key.split(".");
                    let question_index = key_split[0].split("_")[1];

                    if (key_split[2] == "title") {
                        choice_container.option = obj[key];
                        delete obj[key];
                    }

                    else if (key_split[2] == "correctness") {
                        choice_container.correctness = obj[key];
                        delete obj[key];
                    }

                    else if (key_split[2] == "hint") {
                        choice_container.hint = obj[key];
                        delete obj[key];

                        questionnaire.questions[question_index].options.push(choice_container);
                        choice_container = {};
                    }
                }
            }

            // Try to create a questionnaire from the Form
            try {
                await Questionnaire.create(questionnaire);
                request.flash('successMessage', 'Form submitted successfully');
                response.redirect('/management/create');
            }
            catch (err) {
                response.render('error', {
                    error : {
                        status : 500
                    },
                    message: err
                });
            }
        }

        else {
            request.flash('errorMessage', 'Wrong submit type');
            response.redirect('/management/create');
        }
    },

    /**
    * Shows questionnaire modification view
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async modifyQuestionnaire(request, response) {
        Questionnaire.findById(request.params.id, function(err, questionnaire) {
            if (err) {
                response.render('error', {
                    error : {
                        status : 500
                    },
                    message: 'Error while reading questionnaire from database'
                });
            } else {
                response.render('management/modifyQuestionnaire', questionnaire);
            }
        });
    },

    /**
    * Deletes the old questionnaire and creates a new one with updated data
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async updateQuestionnaire(request, response) {

        // Get the current questionnaire and delete it
        const questionnaire = await Questionnaire.findById(request.params.id).exec();

        if(!questionnaire){
            response.render('error', {
                error : {
                    status : 500
                },
                message: `Questionnaire not found,
                questionnaire id: ${request.params.id}`
            });
        }
        else{
            await Questionnaire.findByIdAndDelete(request.params.id).exec();

            let questionnaire = {
                "title" : "",
                "submissions" : "",
                "questions" : []
            };

            let obj = request.body;

            questionnaire.title = obj.questionnaireTitle;
            questionnaire.submissions = obj.submissions;

            delete obj.questionnaireTitle;
            delete obj.submissions;

            let question_container = {};

            // First create the questions into the JSON
            for (let key in obj) {
                if (obj.hasOwnProperty(key)) {
                    let key_split = key.split(".");
                    if (key_split.length == 2 && key_split[1] == "title") {
                        question_container.title = obj[key];
                        delete obj[key];
                    }

                    else if (key_split.length == 2 && key_split[1] == "maxPoints") {
                        question_container.maxPoints = obj[key];
                        question_container.options = [];
                        questionnaire.questions.push(question_container);

                        delete obj[key];
                        question_container = {};
                    }
                }
            }

            let choice_container = {};

            // Then handle the questions
            for (let key in obj) {
                if (obj.hasOwnProperty(key)) {
                    let key_split = key.split(".");
                    let question_index = key_split[0].split("_")[1];

                    if (key_split[2] == "title") {
                        choice_container.option = obj[key];
                        delete obj[key];
                    }

                    else if (key_split[2] == "correctness") {
                        choice_container.correctness = obj[key];
                        delete obj[key];
                    }

                    else if (key_split[2] == "hint") {
                        choice_container.hint = obj[key];
                        delete obj[key];

                        questionnaire.questions[question_index].options.push(choice_container);
                        choice_container = {};
                    }
                }
            }

            // Try to create a questionnaire using the from data
            try {
                await Questionnaire.create(questionnaire);
                request.flash('successMessage', 'Questionnaire updated successfully');
                response.redirect('/management');
            }

            catch (err) {
                response.render('error', {
                    error : {
                        status : 500
                    },
                    message: err
                });
            }
        }
    },

    /**
    * Deletes the a questionnaire by id
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async deleteQuestionnaire(request, response) {

        // Find the righ document
        const questionnaire = await Questionnaire.findById(request.params.id).exec();

        if(!questionnaire){
            response.render('error', {
                error : {
                    status : 500
                },
                message: `Questionnaire not found,
                questionnaire id: ${request.params.id}`
            });
        }
        else{

            // Document found -> delete it
            await Questionnaire.findByIdAndDelete(request.params.id).exec();
            request.flash('successMessage', 'Questionnaire removed successfully.');
            response.redirect('/management');
        }
    },

    /**
    * Deletes a question that is found using the question id
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async deleteQuestion(request, response) {

        // Find parent document in which the choice is
        const parentDoc = await Questionnaire.findById(request.params.pId).exec();

        if(!parentDoc){
            response.render('error', {
                error : {
                    status : 500
                },
                message: `Questionnaire not found,
                questionnaire id: ${request.params.pId}`
            });
        }

        else{

            // When parent foc is found -> fetch right question by id
            // delete it
            parentDoc.questions.pull(request.params.id);
            parentDoc.save(function (err) {
                if (err) {
                    response.render('error', {
                        error : {
                            status : 500
                        },
                        message: `Changes could not be saved,
                        questionnaire id: ${request.params.pId}`
                    });
                }
                else{
                    request.flash('successMessage', 'Question was removed successfully.');
                    response.redirect(`/management/modify/id/${request.params.pId}`);
                }
            });
        }
    },

    /**
    * Deletes a question choice that is found using the choice id
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    async deleteChoice(request, response) {

        // Get the parent document in which the choice is
        const parentDoc = await Questionnaire.findById(request.params.gpId).exec();
        if(!parentDoc){
            response.render('error', {
                error : {
                    status : 500
                },
                message: `Questionnaire not found,
                questionnaire id: ${request.params.pId}`
            });
        }

        else{
            // When parent foc is found -> fetch right question by id
            // and then delete the right choice by id
            parentDoc.questions.id(request.params.pId).options.pull(request.params.id);
            parentDoc.save(function (err) {
                if (err) {
                    response.render('error', {
                        error : {
                            status : 500
                        },
                        message: `Changes could not be saved,
                        questionnaire id: ${request.params.gpId}`
                    });
                }
                else{
                    request.flash('successMessage', 'Question choice was removed successfully.');
                    response.redirect(`/management/modify/id/${request.params.gpId}`);
                }
            });
        }
    }
};
