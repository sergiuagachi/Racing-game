# Racing-game

Jocul dispune de următoarele:
- mașina de culoare roșie cu roțile de culoare gri închis;
- șoseaua de culoare gri cu borduri albastre;
	- este generată în init, nu pe parcursul avansului pe șosea;
- obstacolele sunt piramide portocalii;
	- 1 obstacol dinamic și restul statice;
- pământul de culoare: 
	- verde deschis ziua;
	- verde închis noaptea;
- cerul: albastru deschis ziua și ajune la bleomarin noaptea;
	
- colorarea zi-noapte a pamantului și a cerului sunt realizate în vertex shader;
- la apăsarea tastelor WASD mașina se va deplasa pe ecran;
- la apăsarea tastei Z se schimbă perspectiva între first-person și third-person;
- la apăsarea tastei space se schimbă modul de vizualizare a obiectelor între solid si wire

- funcționalități neimplementate:
	- coliziuni între obiecte;
	- metodă de punctare pe parcusul jocului;
	- metodă de a închide jocul;

O mare parte din proiect este reprezentă de framework-ul pus la dispoziție în cadrul materiei EGC.
Codul ce implementează mai exact jocul se află în fișierele Tema2.cpp, VertexShaderl.glsl și FragmentShader.glsl din folderul sources.
