'use strict';

const express = require('express');

const auth = require('../middleware/auth');

const router = express.Router();
const GamesController = require('../controllers/games');
const OurGameController = require('../controllers/game');
const HelloController = require('../controllers/hello');


router.get('/games', GamesController.listGames);

router.get('/games/id/:id', auth.ensureAuthenticated, OurGameController.showExercise);
router.post('/games/id/:id', auth.ensureAuthenticated, OurGameController.gradeExercise);

router.get('/', HelloController.showExercise);
router.post('/', HelloController.gradeExercise);


module.exports = router;
