var chessboard = document.querySelectorAll('#chessboard div');

var rightButton = document.querySelector('.right-button');
var leftButton = document.querySelector('.left-button');

/************************/
/*   REQUETE CELLULES   */
/************************/


var requete = new XMLHttpRequest();
requete.open('GET', "cellules.json", true);
requete.responseType = 'text';
requete.send();

var cellulesInitiales = [];
var cellulesNouvelles = [];


requete.onload = function(){
    if(requete.readyState == 4 && requete.status == 200){

        var response = requete.response;

        var tmpTab = JSON.parse(response);

        for(var i=0; i<32; i++){
            cellulesInitiales.push(tmpTab[i]);
        }

        for(var i=32; i<tmpTab.length; i++){
            cellulesNouvelles.push(tmpTab[i]);
        }

        // On instancie le plateau
        instanciationPlateau(cellulesInitiales);


        var indexCoup = 0;

        rightButton.addEventListener('click', function(){
            console.log(cellulesNouvelles[cellulesNouvelles.length-1]);
            console.log(indexCoup);

            if(indexCoup>cellulesNouvelles.length-1){
                indexCoup = cellulesNouvelles.length-1;
            }
            else{
                putAPieceOnAPosition(cellulesNouvelles[indexCoup].position, cellulesNouvelles[indexCoup].piece, cellulesNouvelles[indexCoup].couleur, cellulesNouvelles[indexCoup].adr, cellulesNouvelles[indexCoup].csp, cellulesNouvelles[indexCoup].lcp);
                indexCoup++;
            }
        });

        leftButton.addEventListener('click', function(){
            if(indexCoup<0){
                indexCoup = 0;
            }
            else{
                pullAPieceFromAPosition(cellulesNouvelles[indexCoup].position);
                indexCoup--;
            }
        });


    }
}


function instanciationPlateau(cellulesInitiales){
    for(var i=0; i<chessboard.length; i++){
        for(var j=0; j<cellulesInitiales.length; j++){
            if(chessboard[i].getAttribute('id') === cellulesInitiales[j].position){
                chessboard[i].setAttribute('class', cellulesInitiales[j].adr + ',' + cellulesInitiales[j].csp);
                chessboard[i].style.backgroundImage = 'url(' + 'images/pieces/' + cellulesInitiales[j].couleur + '/' + cellulesInitiales[j].piece + '.svg)';
            }
        }
    }
}

function putAPieceOnAPosition(position, piece, couleur, adr, csp, lcp){
    for(var i=0; i<chessboard.length; i++){
        if(chessboard[i].getAttribute('id') === position){
            for(var j=0; j<chessboard.length; j++){
                if(chessboard[j].getAttribute('class').split(',')[1] === adr){
                    chessboard[j].setAttribute('class', '0,0');
                    chessboard[j].style.backgroundImage = '';
                }
            }
            chessboard[i].setAttribute('class', adr + ',' + csp);
            chessboard[i].setAttribute('lcp', lcp);
            chessboard[i].style.backgroundImage = 'url(' + 'images/pieces/' + couleur + '/' + piece + '.svg)';
        }
    }
}

function pullAPieceFromAPosition(position){
    for(var i=0; i<chessboard.length; i++){
        if(chessboard[i].getAttribute('id') === position){
            chessboard[i].style.backgroundImage = '';
        }
    }
}

