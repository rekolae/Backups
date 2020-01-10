'use strict';

// load routers
const UsersRouter = require('./routes/users');
const GamesRouter = require('./routes/game');
const ManagementRouter = require('./routes/management');

// Setup Routes
module.exports = function(app) {
    app.use('/users', UsersRouter);
    app.use('/management', ManagementRouter);
    app.use('/', GamesRouter);

};
