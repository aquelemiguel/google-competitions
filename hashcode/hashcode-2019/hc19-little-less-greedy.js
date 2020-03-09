let _ = require('lodash');
let fs = require('fs');
let file = 'c';
let thresh = 7;
 
let horizontals = [], verticals = [];
let sol = '';
 
fs.readFileSync(file + '.txt', 'utf-8').split('\n').forEach((im, i) => {
    let args = im.split(' ');
    let photo = {}
    photo.id = i;
    photo.orientation = args[0];
    photo.tags = args.slice(2, args.length);
 
    if (photo.orientation === 'H') horizontals.push(photo);
    else verticals.push(photo)
})
 
fs.writeFileSync('out_' + file, horizontals.length + verticals.length / 2 + "\n");
 
// Pair verticals
for (let i = 0; i < verticals.length - 1; i++) {
    for (let j = i + 1; j < verticals.length; j++) {
        let inters = _.intersection(verticals[i].tags, verticals[j].tags)
        if (inters.length === 0) {
            horizontals.push({ id: verticals[i].id + " " + verticals[j].id, orientation: 'H', tags: verticals[i].tags.concat(verticals[j].tags) })
            verticals.splice(i, 1)
            verticals.splice(j - 1, 1)
            i--
            break;
        }
    }
}
 
 
for (let i = 0; i < verticals.length - 1; i += 2) {
    horizontals.push({ id: verticals[i].id + " " + verticals[i + 1].id, orientation: 'H', tags: verticals[i].tags.concat(verticals[i + 1].tags) })
}

let flag = false;
 
for (let i = 0; i < horizontals.length - 1; i++) {
    let photo = null, index2 = -1;
 
    for (let j = i + 1; j < horizontals.length; j++) {
        let out1 = _.intersection(horizontals[i].tags, horizontals[j].tags).length
        let out2 = horizontals[i].tags.length - out1;
        let out3 = horizontals[j].tags.length - out1;
 
        let score = Math.min(out1, out2, out3);
        if (score >= thresh) {
            photo = horizontals[j];
            index2 = j;
            flag = true;
            break;
        }
    }
 
    if(!flag){
        photo = horizontals.pop();
    }
 
    sol += (horizontals[i].id + "\n" + photo.id + "\n");
    //fs.appendFileSync('out_' + file, horizontals[i].id + "\n" + photo.id + "\n");
    if(flag){
        horizontals.splice(i, 1);
        horizontals.splice(index2 - 1, 1); i--;
        flag = false;
    }
    else{
        horizontals.splice(i, 1);
        i--;
    }
}
 
 
fs.appendFileSync('out_' + file, sol);