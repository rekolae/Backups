'use strict';

module.exports = {
    /**
   * Grades excercise
   * @param {Object} request is express request object
   * @param {Array} correctAnswers has correct answers for the exercise
   * @param {Array} maxPointsArray contains max points for each question
   */
    grade(request, correctAnswers, maxPointsArray) {
        const points = [];
        let index = 0;
        const answers = [];

        try {
            //Get all answers for a question
            for(const key in request.body){

                let questionPoints = 0;
                const questionsAnswers = [];
                const answerList = correctAnswers[parseInt(key)];
                let wrongAnswerFound = false;

                if(Array.isArray(request.body[key])){
                //Go through all answers if there are many of them
                    for(let answer of request.body[key]){

                        questionsAnswers.push(answer);
                        //Check correctness of answers
                        if(answerList.includes(parseInt(answer))){
                            questionPoints += (maxPointsArray[index] / correctAnswers[index].length);
                        } else{
                            wrongAnswerFound = true;
                        }
                    }
                }
                //If there is only one answer check it here
                else{
                    let answer = request.body[key];
                    questionsAnswers.push(request.body[key]);
                    if(answerList.includes(parseInt(answer))){
                        questionPoints += (maxPointsArray[index] / correctAnswers[index].length);
                    }
                }

                answers[parseInt(key)] = questionsAnswers;
                if(wrongAnswerFound){
                    questionPoints = 0;
                }
                points[parseInt(key)] = questionPoints;
                index++;
            }
            return [points, '', answers];
        } catch(err){
            const points = -1;
            return [points, err, answers];
        }
    }
};
