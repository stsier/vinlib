const vinlib = require('./build/vinlib.node');
//console.log("vinlib", vinlib);
//console.log("Out: ", vinlib.start("/mnt/d/Nextcloud Sergei/Vintuoso","IMG_3787.jpg","IMG_3765.jpg"));
//console.log("Out: ", vinlib.start());
exports.start = vinlib.start;