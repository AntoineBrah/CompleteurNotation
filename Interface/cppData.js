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

        rightButton.onclick = function(){
            cpt++;

            if(cpt === cellulesCSE.length){
                cpt--;
            }

            console.log(cpt);
            deplacerPieceAvant(cellulesCSE[cpt]);
        }

        leftButton.onclick = function(){

            if(cpt <= 0){
                cpt = 1;
            }



            console.log(cpt);
            deplacerPieceArriere(cellulesCSE[cpt]);

            cpt--;
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
    }


    // Position précédente
    var cellPrec = getCase(getCPP(piece).position);
    cellPrec.setAttribute('currentcell', getCPP(piece).adr);
    cellPrec.style.backgroundImage = 'url(images/pieces/' + piece.couleur + '/' + piece.piece + '.svg)';
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