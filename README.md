# RaycasterProLogik
Jednoduchý raycaster pro logik.

na 10x10 display samozřejmě nejde vidět skoro nic.

Ovládání:
Up - Dopředu
Down - Dozadu
Right - Otočit pohled na pravo
Left - Otočit pohled na levo

int mapa[64]={
1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 4, 0, 0, 0, 0, 1,
1, 0, 3, 0, 0, 0, 0, 1,
1, 0, 2, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 0, 0, 0, 0, 3, 0, 1,
1, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1}

0 - Prostor
1 - Šedá
2 - Červená
3 - Zelená
4 - Modrá

error:jsi ve stěně - hodně světlá bílá
error:neplatné číslo v mapě - fialová

Přetvořeno na logik z opengl originální kód ![zde](https://youtu.be/gYRrGTC7GtA)
