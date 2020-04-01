let str = process.argv[2];

var file = require('fs');

file.readFile(str, function(err, buf){

    let fileArray = [];

    if(err === null){

        let fileContent = buf.toString();

        fileContent = fileContent.split("\n");
        fileContent = fileContent.join(' ');
        fileContent = fileContent.split(" ");

        let pion = new RegExp('[a-h]?x?[a-h]{1}[1-8]{1}(=[QBNR])?[+#]?');
        let piece = new RegExp('[QKBNR]{1}[a-h1-8]?x?[a-h]{1}[1-8]{1}[+#]?');
        let roque = new RegExp('O-O(-O)?');

        let pionProm = new RegExp('[a-h]?x?[a-h]{1}[1-8]{1}(=[QBNR]){1}[+#]?');
        
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
                else if(pionProm.test(x)){

                    let translation2 = '';

                    for(let i=0; i<x.length; i++){
                        switch(x[i]){
                            case 'Q':
                                translation2 += 'D';
                                break;
                            case 'K':
                                translation2 += 'R';
                                break;
                            case 'B':
                                translation2 += 'F';
                                break;
                            case 'N':
                                translation2 += 'C';
                                break;
                            case 'R':
                                translation2 += 'T';
                                break;
                            default:
                                translation2 += x[i];
                                break;
                        }
                    }

                    fileArray.push(translation2);

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
            console.log("NodeJS : Successfully Written to File.\n");
        });
    }
});