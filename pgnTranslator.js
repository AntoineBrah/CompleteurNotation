let str = process.argv[2];

var file = require('fs');

file.readFile(str, function(err, buf){

        let fileArray = [];

        let fileContent = buf.toString();

        fileContent = fileContent.split("\n");
        fileContent = fileContent.join(' ');
        fileContent = fileContent.split(" ");

        let pion = new RegExp('[a-h]?x?[a-h]{1}[1-8]{1}(=[QBNR])?[+#]?');
        let piece = new RegExp('[QKBNR]{1}[a-h1-8]?x?[a-h]{1}[1-8]{1}[+#]?');
        let roque = new RegExp('O-O(-O)?');

        fileContent.forEach(x => {
            if(pion.test(x) || piece.test(x) || roque.test(x)){
                if(piece.test(x)){
                    let translation = '';

                    switch(x[0]){
                        case 'Q':
                            translation += 'D';
                            break;
                        case 'K':
                            translation += 'R';
                            break;
                        case 'B':
                            translation += 'F';
                            break;
                        case 'N':
                            translation += 'C';
                            break;
                        case 'R':
                            translation += 'T';
                            break;
                    }

                    translation += x.substring(1);
                    fileArray.push(translation);

                }
                elseif(new RegExp('[a-h]?x?[a-h]{1}[1-8]{1}(=[QBNR]){1}[+#]?').test()){
                    //On modifie pour la promotion.........
                }
                else{
                    fileArray.push(x);
                }
            }
        });


        let finalString = '';

        for(let i=0; i<fileArray.length; i++){

            if(i%2===0 && i!==0){
                finalString += '\n' + fileArray[i];
            }
            else{

                if(i===0){
                    finalString += fileArray[i];
                }
                else{
                    finalString += ' ' + fileArray[i];
                }
            }
        }

        //console.log(finalString);

        file.writeFile(str, finalString, (err) => {
            if (err) console.log(err);
            console.log("Successfully Written to File.");
        });


});