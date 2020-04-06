var board = document.querySelector('#chessboard');

var chessboard = document.querySelectorAll('#chessboard div');

var chessboardColor = [];

chessboard.forEach(x => {
    var divColor = window.getComputedStyle(x, null).getPropertyValue("background-color");
    chessboardColor.push(divColor);
});

var rightButton = document.querySelector('.right-button');
var leftButton = document.querySelector('.left-button');



/* Reverse Chessboard */
var reverseChessboard = document.querySelector('.reverse');
var linesWhiteSide = document.querySelectorAll('.line-whiteSide');
var columnsWhiteSide = document.querySelectorAll('.column-whiteSide');
var linesBlackSide = document.querySelectorAll('.line-blackSide');
var columnsBlackSide = document.querySelectorAll('.column-blackSide');

var side = 1;

reverseChessboard.onclick = function(){

    if(side%2==0){
        board.style.transform = 'rotate(0deg)';

        columnsWhiteSide.forEach(x => {
            x.style.display = 'inline';
        });

        linesWhiteSide.forEach(x => {
            x.style.display = 'inline';
        });

        columnsBlackSide.forEach(x => {
            x.style.display = 'none';
        });

        linesBlackSide.forEach(x => {
            x.style.display = 'none';
        });

        chessboard.forEach(x => {
            x.style.transform = 'rotate(0deg)';
        });
    }
    else{
        board.style.transform = 'rotate(180deg)';

        columnsBlackSide.forEach(x => {
            x.style.display = 'inline';
        });

        linesBlackSide.forEach(x => {
            x.style.display = 'inline';
        });

        columnsWhiteSide.forEach(x => {
            x.style.display = 'none';
        });

        linesWhiteSide.forEach(x => {
            x.style.display = 'none';
        });

        chessboard.forEach(x => {
            x.style.transform = 'rotate(180deg)';
        });
    }

    side++;
}
/************************/


/************************/
/*   REQUETE CELLULES   */
/************************/


var requete = new XMLHttpRequest();
requete.open('GET', "cellules.json", true);
requete.responseType = 'text';
requete.send();

var cellulesInitiales = [];
var cellulesNouvelles = [];
var toutesLesCellules = [];
var cellulesCSE = [];

var cpt = 0;

requete.onload = function(){
    if(requete.readyState == 4 && requete.status == 200){

        var response = requete.response;

        var tmpTab = JSON.parse(response);

        for(var i=0; i<32; i++){
            cellulesInitiales.push(tmpTab[i]);
            toutesLesCellules.push(tmpTab[i]);
        }

        for(var i=32; i<tmpTab.length; i++){
            cellulesNouvelles.push(tmpTab[i]);
            toutesLesCellules.push(tmpTab[i]);
        }

        for(var i=0; i<cellulesInitiales.length; i++){
            if(cellulesInitiales[i].cse != 0){

                var x = cellulesInitiales[i];
                cellulesCSE.push(x);

                while(x.cse != 0){
                    x = getCSE(x);
                    cellulesCSE.push(x);
                }

                break;
            }
        }

        initialiserPlateau(cellulesInitiales);

        rightButton.onclick = rightMove;
        leftButton.onclick = leftMove;

        document.onkeydown = function(event){
            switch(event.keyCode){
                case 37:
                    leftMove();
                    break;
                case 39:
                    rightMove();
                    break;
            }
        }



        
    }
}

function rightMove(){

    removeColorCase();

    cpt++;

    if(cpt === cellulesCSE.length){
        cpt--;
    }

    console.log(cpt);
    deplacerPieceAvant(cellulesCSE[cpt]);

    estPrisEnPassantRight();
}

function leftMove(){

    removeColorCase();

    if(cpt <= 0){
        cpt = 1;
    }

    console.log(cpt);
    deplacerPieceArriere(cellulesCSE[cpt]);

    estPrisEnPassantLeft();

    cpt--;
}

chessboard.forEach(x => {
    x.addEventListener('click', function(){
        printListesCoupPossibles(x);
    });
});

//prise en passant et roque
function estPrisEnPassantRight(){
    chessboard.forEach(x => {

        if(x.getAttribute('currentcell') != 0){

            let p = getPiece(x.getAttribute('currentcell'));
            let lcp = p.lcp.split(',');

            if(lcp[cpt] == undefined){ // Pion ou Tour qu'on efface quand on avance dans la partie

                x.setAttribute('i' + cpt, x.getAttribute('currentcell'));
                x.setAttribute('currentcell', 0);
                x.style.backgroundImage = '';

                if(p.piece === "Tour"){ // Tour qu'on fait apparaitre au moment du roque
                    let p2 = getPiece(p.csp);
                    let cell = getCase(p2.position);

                    console.log(p2);

                    cell.setAttribute('currentcell', p2.adr);
                    cell.setAttribute('r'+cpt, p2.adr);
                    cell.style.backgroundImage = 'url(images/pieces/' + p2.couleur + '/' + p2.piece + '.svg)';

                }

            }
        }

    });
}

//prise en passant et roque
function estPrisEnPassantLeft(){
    chessboard.forEach(x => {

        if(x.getAttribute('i'+cpt) !== null && x.getAttribute('currentcell') == 0){//Tour ou pion qu'on fait réapparaitre quand on revient en arriere

            let p = getPiece(x.getAttribute('i'+cpt));
            x.setAttribute('currentcell', p.adr);
            x.style.backgroundImage = 'url(images/pieces/' + p.couleur + '/' + p.piece + '.svg)';
        }

        if(x.getAttribute('r'+cpt) !== null && x.getAttribute('currentcell') != 0){ //Tour qu'on efface quand on revient en arrière

            let p = getPiece(x.getAttribute('r'+cpt));
            x.removeAttribute('r'+cpt);
            x.setAttribute('currentcell', 0);
            x.style.backgroundImage = '';
        }

    });
}


var instancierPiece = (piece) => {
    var cell = getCase(piece.position);
    cell.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';
}

var deplacerPieceAvant = (piece) => {
    // Position actuelle
    var cell = getCase(piece.position);

    if(cell.getAttribute('currentcell') !== piece.adr && cell.getAttribute('currentcell') != 0){
        cell.setAttribute('i' + cpt, cell.getAttribute('currentcell'));
    }

    cell.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';
    cell.setAttribute('currentcell', piece.adr);

    // Position précédente
    var cellPrec = getCase(getCPP(piece).position);
    cellPrec.style.backgroundImage = '';
    cellPrec.setAttribute('currentcell', '0');
}

var deplacerPieceArriere = (piece) => {
    // Position actuelle
    var cell = getCase(piece.position);
    cell.style.backgroundImage = '';
    cell.setAttribute('currentcell', '0');

    if(cell.getAttribute('i'+cpt) != null){
        let p = getPiece(cell.getAttribute('i'+cpt));
        cell.style.backgroundImage = 'url(images/pieces/' + p.couleur + '/' + p.piece + '.svg)';
        cell.setAttribute('currentcell', cell.getAttribute('i'+cpt));
    }

    // Position précédente
    var cellPrec = getCase(getCPP(piece).position);
    cellPrec.setAttribute('currentcell', getCPP(piece).adr);
    cellPrec.style.backgroundImage = 'url(images/pieces/' + getCPP(piece).couleur + '/' + getCPP(piece).piece + '.svg)';
} 

var initialiserPlateau = (pieces) => {
    pieces.forEach(x => {
        var cell = getCase(x.position);
        cell.setAttribute('currentcell', x.adr);
        instancierPiece(x);
    });
}

var getPiece = (adr) => {
    for(let i=0; i<toutesLesCellules.length; i++){
        if(adr === toutesLesCellules[i].adr){
            return toutesLesCellules[i];
        }
    }
    return 0;
}

var getCSP = (piece) => {
    for(let i=0; i<toutesLesCellules.length; i++){
        if(piece.csp === toutesLesCellules[i].adr){
            return toutesLesCellules[i];
        }
    }
    return 0;
}

var getCPP = (piece) => {
    for(let i=0; i<toutesLesCellules.length; i++){
        if(piece.cpp === toutesLesCellules[i].adr){
            return toutesLesCellules[i];
        }
    }
    return 0;
}

var getCSE = (piece) => {
    for(let i=0; i<toutesLesCellules.length; i++){
        if(piece.cse === toutesLesCellules[i].adr){
            return toutesLesCellules[i];
        }
    }
    return 0;
}

function getCase(position){
    for(let i=0; i<chessboard.length; i++){
        if(chessboard[i].getAttribute('id') === position){
            return chessboard[i];
        }
    }
}


/************************/
/*     AFFICHAGE LCP    */
/************************/

function printListesCoupPossibles(cell){
    if(cell.getAttribute('currentcell') != 0){

        let p = getPiece(cell.getAttribute('currentcell'));
        let lcp = p.lcp.split(',');

        console.log(lcp, "| cpt = ", cpt);
        
        removeColorCase();
        colorierCase(lcp[cpt].split(' '));   
    }
    else{
        removeColorCase();
    }
}

function colorierCase(posTab){
    chessboard.forEach(x => {
        posTab.forEach(y => {
            if(x.getAttribute('id') === y){
                x.style.backgroundColor = 'yellow';
            }
        })
    });
}

function removeColorCase(){
    for(let i=0; i<chessboard.length; i++){
        chessboard[i].style.backgroundColor = chessboardColor[i];
    }
}


/********************************/
/*   AFFICHAGE PARTIE INITIALE  */
/********************************/
/*
function printPartieInitiale(){

    var file = require('fs');

    file.readFile = function(err, buf){

        let fileContent = buf.toString();

        fileContent = fileContent.split("\n");
        fileContent = fileContent.join(' ');

        console.log(fileContent);
    }

}
*/