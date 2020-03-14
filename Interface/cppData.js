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

        console.log(cellulesInitiales);

        for(var i=32; i<tmpTab.length; i++){
            cellulesNouvelles.push(tmpTab[i]);
        }


    }
}
