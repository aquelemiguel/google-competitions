let fs = require('fs');

let file = "e";

// H 3 cat beach sun
// V 2 selfie smile
// V 2 garden selfie
// H 2 garden cat
let horizontals = [], verticals = [];

function getCommonElements(arrays) { //Assumes that we are dealing with an array of arrays of integers
    var currentValues = {};
    var commonValues = {};
    for (var i = arrays[0].length - 1; i >= 0; i--) {//Iterating backwards for efficiency
        currentValues[arrays[0][i]] = 1; //Doesn't really matter what we set it to
    }
    for (var i = arrays.length - 1; i > 0; i--) {
        var currentArray = arrays[i];
        for (var j = currentArray.length - 1; j >= 0; j--) {
            if (currentArray[j] in currentValues) {
                commonValues[currentArray[j]] = 1; //Once again, the `1` doesn't matter
            }
        }
        currentValues = commonValues;
        commonValues = {};
    }
    return Object.keys(currentValues).map(function (value) {
        return value;
    });
}

fs.readFileSync(file + '.txt','utf-8').split('\n').forEach((im, i) => {
    let args = im.split(' ');
    let photo = {}
    photo.id = i;
    photo.orientation = args[0];
    photo.tags = args.slice(2, args.length);

    if (photo.orientation === 'H') horizontals.push(photo);
    else verticals.push(photo)
})

fs.writeFileSync('out_' + file, horizontals.length + verticals.length / 2 + "\n");

for (let i = 0; i < horizontals.length - 1; i++) {
    let max = -1, photo = null, index2 = -1;

    for (let j = i+1; j < horizontals.length; j++) {
        let out1 = getCommonElements([horizontals[i].tags, horizontals[j].tags]).length
        let out2 = horizontals[i].tags.length - out1;
        let out3 = horizontals[j].tags.length - out1;

        let score = Math.min(out1, out2, out3);
        if (score > max) { max = score; photo = horizontals[j]; index2 = j; }
    }
    fs.appendFileSync('out_' + file, horizontals[i].id + "\n" + photo.id + "\n");
    horizontals.splice(i, 1);
    horizontals.splice(index2 - 1, 1); i--; 
}

for (let i = 0; i < verticals.length - 1; i+=2) {
    fs.appendFileSync('out_' + file, verticals[i].id + " " + verticals[i+1].id + "\n")
}
