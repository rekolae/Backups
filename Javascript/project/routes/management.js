'use strict';

const express = require('express');
const expressSanitizer = require('express-sanitizer');

const auth = require('../middleware/auth');

const router = express.Router();

router.use(express.urlencoded({extended: true}));
router.use(express.json());
router.use(expressSanitizer());

const ManagementController = require('../controllers/management');

router.get('/', auth.ensureTeacher, ManagementController.showManagementOptions);

router.get('/create', auth.ensureTeacher, ManagementController.createQuestionnaire);
router.post('/create/type/:type', auth.ensureTeacher, ManagementController.parseQuestionnaire);

router.get('/modify/id/:id', auth.ensureTeacher, ManagementController.modifyQuestionnaire);
router.post('/modify/id/:id/update', auth.ensureTeacher, ManagementController.updateQuestionnaire);

router.get('/delete/id/:id', auth.ensureTeacher, ManagementController.deleteQuestionnaire);
router.get('/delete/parentId/:pId/id/:id', auth.ensureTeacher, ManagementController.deleteQuestion);
router.get('/delete/grandparentId/:gpId/parentId/:pId/id/:id', auth.ensureTeacher, ManagementController.deleteChoice);

module.exports = router;
