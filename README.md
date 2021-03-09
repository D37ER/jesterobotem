# jesterobotem
Idziemy w stronę światła.

Celem naszego projektu jest zbudowanie systemu komputerowego, którego będę nazywał robotem, bo kanał na discordzie tak się nazywa.
Robot ten będzie miał na celu ustawienie panelu słonecznego w odpowiednim kierunku i pod odpowiednim kątem, aby optymalnie padało na niego światło słoneczne.
Ale to nie wszystko. Jeżeli będzie nam szło w miarę sprawnie to robot ten ma też mieć możliwość podłączenia do niego kierunkowej anteny i ustawiania jej w najlepszym możliwym położeniu. 
Ostatecznie możnaby się bawić i wykorzystać system do ustawiania np. kamery pod najlepszym kątem (ale to już tylko gdybanie)

Żeby dało się ten system wykorzystać więcej niż jednego zastosowania podzielimy go na dwie części.
Z braku lepszych pomysłów nazwałem je System A i System B.

 - System A to ten ważniejszy, który dostaje ustandaryzowany sygnał i ustawia nasz panel w odpowiednim kierunku.
 - System B to np. nasz panel słoneczny (albo inne czujniki), które określają jak dobrze pada słońce na nasz panel. System ten docelowo będzie przetwarzał analogowy sygnał na cyfrowy i wysyłał go do systemu A.
 
System A musi działać tylko na podstawie jednej danej wejściowej która będzie jakoś ustandaryzowana. Będzie to poziom sygnału (światła) w ustalonej przez nas skali np. 0-100, 0-256, 0-1024. Zobaczymy na co nam pozwili pamięć Arduino i wtedy zdecydujemy jak będzie wyglądać sygnał.
 
Ponieważ zbudowanie fajnego projektu to jedna sprawa a dostanie zadowalającej oceny to druga (A każdy może mieć inne priorytety) poniżej przedstawiam plan działania.

Plan działania <br>
<ol>
 <li>
  DONE Zdecydowanie się na podstawowe części (silniki, sensory, wstępna obudowa).
 </li>
 <li>
  Zbudowanie pierwszego modelu póki co sytemy A i B nie są rozróżnialne, ponieważ są podłączone do płytki Arduino.
 </li>
 <li>
  Podłączenie laptopa, żeby każdy z nas mógł się łączyć z arduino i wgrywać swoją wersję projektu.
 </li>
 <li>
  Burza mózgów w jaki sposób nasz robocik będzie swoje miejsce wyznaczał. (Jak szybko się ma poruszać, oraz na jakiej zasadzie ograniczać pole skanowania).
 </li>
 <li>
  Na początku projektujemy system w języku wyższego poziomu niż assembler. Będzie to jakiś język podobny do C na którym domyślnie chodzi arduino. Staramy się zbudować program który po prostu będzie dobrze działać.
 </li>
 <li>
  Postaramy się wycisnąć z Arduino co się da, tak żeby nasz system działał na tyle sprawnie na ile się da.
 </li>
 <li>
  (w ostateczności opcjonalny krok) Gdy będziemy zadowoleni z naszego stworzenia zaczynamy pracować nad protokołem połączenia tych dwóch systemów. Myślę, że najlepiej jeżeli będziemy cyfrowo komunikować się z Systemem A. Będziemy starali się rozdzielić System A od Systemu B. Być może wykorzystamy do tego drugie arduino. Chodzi tutaj o to żeby możliwe było później podłączenie komputera/tabletu/ogólnie urządzenia z wifi/4G, które będzie sobie liczyło samemu jak dobry jest sygnał i przekazywało sygnał w naszej ustandaryzowanej skali (patrz wyżej). Gdy to osiągniemy będziemy mogli podłączyć jakikolwiek system do naszego robocika i optymalizować cokolwiek chcemy.
 </li>
</ol>
2.  <br>
3.  <br>
4.  <br>
5.  <br>
6.  <br>
7.  <br>

No i teraz staramy się w miarę możliwości i chęci iść w górę naszej tabeli ocen. <br>

8. Zasadniczo to co czego płytkę trzeba będzie wytrawić, oraz na ile wymagany jest assembler i jak cały sprzęt ma być surowy dowiemy się na jakiś zajęciach. <br>
