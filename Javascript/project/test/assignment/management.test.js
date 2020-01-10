/* eslint-disable no-console */
'use strict';

require('dotenv').config();
const config = require('config');
const http = require('http');
const chai = require('chai');
const chaiHttp = require('chai-http')
const expect = chai.expect;
const Questionnaire = require('../../models/questionnaire');
const app = require('../../app.js');
const admin = config.get('admin');
const managementUrl = '/management/create';
const User = require('../../models/user');
chai.use(chaiHttp);
chai.should();
let request = chai.request.agent(app);

describe('Management CRUD tests', function() {

	beforeEach(async function() {
		try {
            // remove all users from the database and re-create admin user
            await User.deleteMany({});

            const userData = {...admin, role: 'admin'};
            const user = new User(userData);
            await user.save();
        } catch (err) {
            // eslint-disable-next-line no-console
            console.log(err);
            throw err;
        }
    });

	let payload = {
		'title': 'test_q',
		'submissions': '2',
		'questions': []
	};

	describe('Management READ tests', function() {
		it("questionnaires should have questionnaire named 'Count without a calculator'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='Count without a calculator'){
						expect(questionnaires[i].title).equal('Count without a calculator');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
		it("questionnaires should have questionnaire named 'Our very own magical question set'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='Our very own magical question set'){
						expect(questionnaires[i].title).equal('Our very own magical question set');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
		it("questionnaires should have questionnaire named 'Larger questionnaire to check switching questions, max 15'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='Larger questionnaire to check switching questions, max 15'){
						expect(questionnaires[i].title).equal('Larger questionnaire to check switching questions, max 15');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
		it("questionnaires should have questionnaire named 'BWA questionnaire'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='BWA questionnaire'){
						expect(questionnaires[i].title).equal('BWA questionnaire');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
		it("questionnaires should NOT have questionnaire named 'This should not be'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				expect(questionnaires[0].title).not.equal('This should not be');
			});
		});
		it("questionnaire ('Count without a calculator') should have atleast 1 question", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				expect(questionnaires[0].questions.length).not.equal(0);
			});
		});
		it("questionnaire ('Our very own magical question set') should have atleast 1 question", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				expect(questionnaires[1].questions.length).not.equal(0);
			});
		});
		it("questionnaire ('Larger questionnaire to check switching questions, max 15') should have atleast 1 question", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				expect(questionnaires[2].questions.length).not.equal(0);
			});
		});
		it("questionnaire ('BWA questionnaire') should have atleast 1 question", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				expect(questionnaires[3].questions.length).not.equal(0);
			});
		});
	});

	describe('Management DELETE tests', function() {
		it("Management delete questionnairre 'Count without a calculator'", async function() {
			//finds id for question
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='Count without a calculator'){
						var id = questionnaires[i]._id;
						//Deletes question
						Questionnaire.findByIdAndDelete(id).exec();
					}
				}
			});
		});
		it("Management check 'Count without a calculator' does not exits after deleting", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='Count without a calculator'){
						expect(questionnaires[i].title).not.equal('Count without a calculator');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').not.equal('');
					}
				}
			});
		});
	});

	describe('Management CREATE tests', function() {
		it("CREATE questionnaire set title 'test_q'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				payload.questions.push(questionnaires[0].questions[0]);
				Questionnaire.create(payload);
			});
		});
		it("Find just created questionary ('test_q')'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='test_q'){
						expect(questionnaires[i].title).equal('test_q');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
	});

	describe('Management UPDATE tests', function() {
		it("UPDATE questionnaire set title 'Count without a calculator' to 'test_q'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				questionnaires[0].title = 'test_q';
			});
		});
		it("Find just created questionary ('test_q')'", async function() {
			Questionnaire.find({}, function(err, questionnaires) {
				var i;
				for (i = 0; i < questionnaires.length; i++) {
					if(questionnaires[i].title=='test_q'){
						expect(questionnaires[i].title).equal('test_q');
						break;
					}
					else if(i==questionnaires.length-1){
						expect('questionnaire not found').equal('');
					}
				}
			});
		});
	});
});
