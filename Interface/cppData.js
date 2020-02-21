var chessboard = document.querySelectorAll('#chessboard div');

/************************/
/*   REQUETE CELLULES   */
/************************/


var requete = new XMLHttpRequest();
requete.open('GET', "cellules.json", true);
requete.responseType = 'text';
requete.send();


requete.onload = function(){
    if(requete.readyState == 4 && requete.status == 200){

        var response = requete.response;

        var myTab = JSON.parse(response);

        for(var i=0; i<chessboard.length; i++){
            for(var j=0; j<myTab.length; j++){
                
                if(chessboard[i].getAttribute('id') === myTab[j].position){
                    
                    chessboard[i].style.backgroundImage = 'url(' + 'images/pieces/' + myTab[j].couleur + '/' + myTab[j].piece + '.svg)';
                }
            }
        }




    }
}

