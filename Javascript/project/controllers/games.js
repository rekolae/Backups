'use strict';

const Questionnaire = require('../models/questionnaire');

module.exports = {
    /**
    * Gets all questionnaires from the database and shows game page
    * @param {Object} request is express request object
    * @param {Object} response is express response object
    */
    listGames(request, response) {
        Questionnaire.find({}, function(err, questionnaires) {
            if (err) {
                response.render('error', {
                    error : {
                        status : 500
                    },
                    message: 'Error while reading questionnaires from database'
                });
            } else {
                response.render('gameList', questionnaires);
            }
        });
    }
};
