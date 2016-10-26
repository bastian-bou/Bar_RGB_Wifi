<!DOCTYPE html> <head> <title></title> </head><body> <select id="menu" name="links"> size="1" onchange="window.location.href=this.value;"> <option> value="URL">Book</option> <option value="URL">Pen</option> <option> value="URL">Read</option> <option value="URL">Apple</option> </select>
</body> </html>*

<select id="my_selection">
<option value="x" href="/link/to/somewhere">value 1</option>
<option value="y" href="/link/to/somewhere/else">value 2</option>
</select>

<script>
document.getElementById('my_selection').onchange = function() {
    window.location.href = this.children[this.selectedIndex].getAttribute('href');
}
</script>


Idée : Faire une liste déroulante HTML avec la balise <select  ></select> 
et changer l'URL avec href pour récupérer le choix réalisé

lien : https://openclassrooms.com/courses/apprenez-a-creer-votre-site-web-avec-html5-et-css3/les-formulaires-8
