/*
* Importation du module électron +
* définition de raccourcis vers des objets
* que nous utiliserons souvent.
*/
const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;

const nativeImage = require('electron').nativeImage;
var image = nativeImage.createFromPath(__dirname + '/images/icones/icon.png');
image.setTemplateImage(true);

/*
* Code d'initialisation d'une fenêtre
*/

let mainWindow;

function createWindow(){

    // On définit une taille pour notre fenêtre
    mainWindow = new BrowserWindow({
        width: 1400, 
        height: 800,
        resizable: false,
        frame: false,
        icon: image,
        title: 'Completeur de Notation'
    });

    // On est obligé de passer par un chemin absolu
    // index.html est la page a afficher
    mainWindow.loadURL(`file://${__dirname}/index.html`);

    // Lorsque la fenêtre est fermé, on définit la fenêtre à null
    // Pour cela, on utilise l'événement 'closed' de la fenetre principale
    mainWindow.on('closed', () => {
        mainWindow = null;
    });
}

/*
* Maintenant, il faut appeler la méthode que nous venons de créer lorsque l’application démarre. 
* Pour cela, il faut la lier avec l’évènement 'ready' de notre constante app.
*/
app.on('ready', createWindow);

/*
* Mais le script principal continuera à tourner même quand on aura fermée notre fenêtre. 
* On va devoir utiliser l’évènement window-all-closed d’app, qui est émit quand toutes les fenêtres ont étés fermées. 
* À ce moment, on va utiliser la méthode app.quit qui va nous permettre de quitter l’application.
*/

app.on('window-all-closed', () => {
    if(process.platform !== 'darwin'){
        app.quit();
    }
})

app.on('activate', () => {
    if(mainWindow === null){
        createWindow();
    }
})



