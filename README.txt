# Running the game --------------------------------------------------------------------------------------
1. Go into the project directory.
2. Run "make all"
3. Run "make run"
4. Follow the instructions on screen to select your map.
5. Play

!! Warning the game may not start if launched from a code editor. Using a basic terminal window is recommended.
The game needs a few rows of the command line window to display the game map and some editors (like CLion) always return the available row amount as 1. 

# Oficiální zadání --------------------------------------------------------------------------------------

Ant wars

Naprogramujte jendoduchou hru války několika mravenčích klanů. Mravenci se rodí v mraveništích a lze jim zadat cíl - jiné mraveniště.

Na cizí mraveniště mravenci útočí, vlastní opevňují.

Váš engine:

ze souboru nahraje mapu s lokacemi mraveništ a překážek
implementuje triviální interakci mravenec vs. mravenec (např. jeden zabije jednoho)
implementuje jednoduchou škálovanou AI řídící organizaci klanů mravenců
umožňuje ukládat a načítat rozehrané hry
Engine může fungovat real-time hra, či tahová hra.

Jak může vypadat mapa?

" " - prázdné místa pro pohyb mravenců
A a B (resp Z,Y,X a W pro druhého hráče) označují mraveniště s daným počtem mravenců uvnitř
a,b (resp z,y,x,w) označují jednotlivé mravence
zadané cesty lze označit (v ukázce A->B, B->Y, Y->B, W->Y, X->Y, Z->Y, např. z mraveniště Z vyrazilo 5 mravenců a dalších 6 ještě vyjde po zadané cestě

##################################################
#                                                #
#                                                #
#     █████           █████                      #
#     █A13█aaaaaaaaaaa█B20█                      #
#     █████           █████                      #
#                          b                     #
#                          b                     #
#                           b                    #
#########################   b              █████ #
#                            b             █W03█ #
#                            y             █████ #
#                             y         -ww      #
#                             y     <---         #
#       █████                  █████       █████ #
#       █Z06█zzzzz------------>█Y30█<-xx--x█X01█ #
#       █████                  █████       █████ #
#                                                #
##################################################
Kde lze využít polymorfismus? (doporučené)

Parametry útočníků: znak, barva, písmeno, ...
Políčka mapy: volno, věž, mravenec...
Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...
Při implementaci se pokuste implementovat nějaké vlastní zajímavé prvky.

Ukázky:

http://www.auraluxgame.com/
http://www.superhry.cz/games/2072/
http://store.steampowered.com/app/357930/




# Vlastní úprava --------------------------------------------------------------------------------------

Hra The Many Nations of Fastfood

Situácia medzi miestnymi národnostnými Fastfood reťazcami sa vyvinula v poriadny konfilkt.
V záujme získať monopol a vytlačit konkurenciu z mesta pribudla v každom podniku pozícia reprezentanta spoločnosti,
ktorého cieľom dostať sa do nepriateľského podniku a spôsobiť tam čo najväčší chaos. Každý reprezentant, zaneprázdni práve
jedného reprezentanta, ktorý takto čaká vo svojom podniku, tí sa potom pochopiteľne uhádajú k smrti.
Ak sa reprezentanti stretnú už po ceste, začnú nekonečnú hádku a dajú sa považovať za ďalej nepoužitelných.
Po chvíľke je každý otvorený podnik schopný najať nové posily.
Vašou úlohou je byť posledným reťazcom, ktorému ostanú základne(podniky) pre reprezetantov.

Hra sa bude ovládať pomocou klávesnice a bude implementovaná ako ťahová hra.

- `n ...` vytvorí novú hru podľa zadaných parametrov (level, difficulty...)
- `l... [filename]` načíta hru do súboru
- `s... [filename]` uloží hru do súboru
- `[establishment number]` zvolí podnik pre útok
- `q` ukončí program


Po spustení sa program dostane do triedy `CStartMenu`, kde čaká na príkazy pre začiatok novej hry alebo načítanie zo súboru.
Ten spustí triedu s vygenrovanou mapou a stavom hry `CGame` , ktorá sa stará o priebeh hry.

Trieda `CMap` sa stará o mapu a objekty v nej. Objekt v mape je instancia triedy `CViewableItem`, z ktorej dedia triedy
`CRepresentative` strarajúci sa o jednotlivých reprezentantov, `CEstablishment` ktorý zastupuje základňu(podnik), `CObstacle` zastupujúci
neprejditeľné prekážky a `CNothing` pre prázdne miesta.

Trieda `CAction` prevádzkuje jednotlivé pohyby jednotiek po mape.
O hráčov sa stará abstraktná trieda `CPlayer`, ktorá sa ďalej delí na `CHuman` ovládanú človekom a `CComputer` ovládanú počítačom.

Každé kolo každý `CPlayer` vytvorí nový ťah pomocou triedy `CAction`, potom ako každý podnik spravil nejaký ťah sa ťahy
pozbierajú, spracujú a odsimuluje sa priebeh kola. Po každom kole je možné hru uložit do súboru. Tento súbor je možné
pri následnom spustení hry načítať a pokračovať v rozohranej hre.


Z grafickej stránky sa hra bude funkčne podobať na obrázok vyššie ↑↑↑, pričom sa využije konzolové prostredie s podporou
c++ knižnice ncurses(resp. curses).

Ku hre bude dodaná aj zložka obsahujúca dopredu vygenerované mapy a uložené hry, ktoré bude možné spustiť ako jednotlivé levely.

# Polymorfizmus --------------------------------------------------------------------------------------

Polymorfizmus využívam vo `CViewableItem`, kde jednotlivé objekty v mape majú rôzne vlastnosti a spôsoby zobtrazenia podľa typu.
Konkrétne ide o funkcie `Show`, ktorá hovorí ako sa má na mape daný objekt zobraziť, `Walkable`, kde je odopoveďou na otázku
či je možné cez daný objekt prejsť true alebo false. Tento polymorfizmus by určite šiel naradiť vhodnou funkciou,
avšak kedže bude slúžiť najmä pre porovnanie vlastností a typov príde mi prehľadnejšie mať to uvedené v každej triede samostatne.

Polymorfizmus v abstraktnej triede `CPlayer` má metódu `MakeAction`, ktorá v `CHuman` bude čakať na input od hráča,
podľa čoho následne vyberie začiatočnú a koncovú základňu, u `CComputer` metóda `MakeAction` vygeneruje pohyb cez jedno z implementovaných AI
podľa zvolenej obtiažnosti.
