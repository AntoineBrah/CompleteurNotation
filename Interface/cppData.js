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
var toutesLesCellules = [];
var cellulesCSE = [];


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

        var cpt = 0;

        console.log(cpt);

        rightButton.onclick = function(){
            cpt++;

            if(cpt === cellulesCSE.length){
                cpt--;
            }
            
            if(cpt < cellulesCSE.length){
                deplacerPieceAvant(cellulesCSE[cpt]);
            }

            console.log(cpt);
        }

        leftButton.onclick = function(){
            cpt--;

            if(cpt === -1){
                cpt = 0;
            }

            if(cpt >= 0){
                deplacerPieceArriere(cellulesCSE[cpt]);
            }

            console.log(cpt);
        }


    }
}



var instancierPiece = (piece) => {
    var cell = getCase(piece.position);
    cell.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';
}

var deplacerPieceAvant = (piece) => {
    // Position actuelle
    var cell = getCase(piece.position);
    cell.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';
    cell.setAttribute('currentcell', piece.adr);

    // Position précédente
    var cellPrec = getCase(getCPP(piece).position);
    cellPrec.style.backgroundImage = '';
    cellPrec.setAttribute('currentcell', '0');
    cellPrec.setAttribute('previousCell', getCPP(piece).adr);
}

var deplacerPieceArriere = (piece) => {
    // Position actuelle
    var cell = getCase(piece.position);
    cell.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';

    // Position suivante
    var cellSuiv = getCase(getCSP(piece).position);
    console.log("ok : ", cellSuiv);
    cellSuiv.style.backgroundImage = '';
} 


var initialiserPlateau = (pieces) => {
    pieces.forEach(x => {
        var cell = getCase(x.position);
        cell.setAttribute('previousCell', x.cpp);
        instancierPiece(x);
    });
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