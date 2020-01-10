/* eslint-disable no-console */
/* eslint-disable no-invalid-this */
'use strict';

require('dotenv').config();
const config = require('config');
const http = require('http');
const Browser = require('zombie');
const chai = require('chai');
const expect = chai.expect;
const Questionnaire = require('../../models/questionnaire');

const app = require('../../app.js');
const admin = config.get('admin');
const port = 3333;

let server;
let browser;

async function auth(browser) {
    // Load login page
    await browser.visit('/users/login');

    // Fill in login information and login
    browser.fill('email', admin.email);
    browser.fill('password', admin.password);
    await browser.pressButton('#btnLogin');
}

describe('OurGame (BWA questionnaire)', function() {
    beforeEach(async function() {
        server = http.createServer(app).listen(port);
        Browser.localhost('bwa', port);
        browser = new Browser();
        await auth(browser);
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='BWA questionnaire'){
                        browser.visit('/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('page not found').equal('');
                    }
                }
        });
    });

    afterEach(async function() {
        server.close();
    });

    it('OurGame (BWA questionnaire) downloaded successfully', function(){
        browser.assert.success();
    });

    it('must have a form with POST method', function() {
        browser.assert.element('form[method="POST"]');
    });

    it('must have a form with submit button', function() {
        browser.assert.element('form button[type="submit"]');
    });

    it('the submit button must have id "grade"', function() {
        browser.assert.element('#grade');
        browser.assert.element('button#grade');
    });
});

describe('OurGame (Our very own magical question set)', function() {
    beforeEach(async function() {
        server = http.createServer(app).listen(port);
        Browser.localhost('bwa', port);
        browser = new Browser();
        await auth(browser);
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='Our very own magical question set'){
                        browser.visit('/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('page not found').equal('');
                    }
                }
        });
    });

    afterEach(async function() {
        server.close();
    });

    it('OurGame (Our very own magical question set) downloaded successfully', function(){
        browser.assert.success();
    });

    it('must have a form with POST method', function() {
        browser.assert.element('form[method="POST"]');
    });

    it('must have a form with submit button', function() {
        browser.assert.element('form button[type="submit"]');
    });

    it('the submit button must have id "grade"', function() {
        browser.assert.element('#grade');
        browser.assert.element('button#grade');
    });
});

describe('OurGame (Larger questionnaire to check switching questions, max 15)', function() {
    beforeEach(async function() {
        server = http.createServer(app).listen(port);
        Browser.localhost('bwa', port);
        browser = new Browser();
        await auth(browser);
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='Larger questionnaire to check switching questions, max 15'){
                        browser.visit('/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('page not found').equal('');
                    }
                }
        });
    });

    afterEach(async function() {
        server.close();
    });

    it('OurGame (Larger questionnaire to check switching questions, max 15) downloaded successfully', function(){
        browser.assert.success();
    });

    it('must have a form with POST method', function() {
        browser.assert.element('form[method="POST"]');
    });

    it('must have a form with submit button', function() {
        browser.assert.element('form button[type="submit"]');
    });

    it('the submit button must have id "grade"', function() {
        browser.assert.element('#grade');
        browser.assert.element('button#grade');
    });
});