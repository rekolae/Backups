require('dotenv').config();
const config = require('config');
const http = require('http');
const Browser = require('zombie');

const app = require('../../app.js');
const admin = config.get('admin');
const port = 3333;
const Questionnaire = require('../../models/questionnaire');

async function auth(browser) {
    // Load login page
    await browser.visit('/users/login');

    // Fill in login information and login
    browser.fill('email', admin.email);
    browser.fill('password', admin.password);
    await browser.pressButton('#btnLogin');
}

describe('Check games page content', function() {
    let server;
    let browser;

    beforeEach(async function() {
        server = http.createServer(app).listen(port);
        Browser.localhost('bwa', port);
        browser = new Browser();
        await auth(browser);
        await browser.visit('/games');
    });

    afterEach(async function() {
        server.close();
    });

    it('/games downloaded successfully', function(){
        browser.assert.success();
    });

    it('/games must have a link to Hello A+ game',function() {
        browser.assert.link('a', 'Hello A+', '/');
    });

    it('/games must have a link to BWA questionnaire',function() {
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='BWA questionnaire'){
                        browser.assert.link('a', 'BWA questionnaire', '/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('Link not found').equal('');
                    }
                }
        });
    });

    it('/games must have a link to Our very own magical question set',function() {
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='Our very own magical question set'){
                        browser.assert.link('a', 'Our very own magical question set', '/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('Link not found').equal('');
                    }
                }
        });
    });

    it('/games must have a link to Larger questionnaire to check switching questions, max 15',function() {
        Questionnaire.find({}, function(err, questionnaires) {
                var i;
                for (i = 0; i < questionnaires.length; i++) {
                    if(questionnaires[i].title=='Larger questionnaire to check switching questions, max 15'){
                        browser.assert.link('a', 'Larger questionnaire to check switching questions, max 15', '/games/id/'+questionnaires[i]._id);
                        break;
                    }
                    else if(i==questionnaires.length-1){
                        expect('Link not found').equal('');
                    }
                }
        });
    });
});
