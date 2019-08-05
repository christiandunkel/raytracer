
# Theoretical Tasks
[Back to main page](../README.md)

This page contains all answers to the theoretical tasks of assignment 1 to 7. Tasks without any theoretical questions are excluded from this page.

## Aufgabe 1.3
Die kleinstmögliche Zahl, die durch 1 bis 20 teilbar ist, ist `232792560`.

## Aufgabe 1.4
**Allgemeiner Aufbau:**
 `Typ Name = Wert;`

![Aufgabenstellung](aufgabe_1_4.PNG)

 - int a = 9; `Ganzzahl` 
 - bool b = false; `Wahrheitswert` 
 - char c = 'a'; `Zeichentyp` 
 - double d = 1.3; `Fließkommazahl` 
 - int const five = 5; `nicht veränderbare Ganzzahl` 
 - double e = a/five; `ergibt 1.0, da erst Teilen von int, dann parse zu double` 
 - five = d; `nicht möglich, da Konstante`

## Aufgabe 1.5
`Initialisierung` Erst-Zuweisung eines Wertes, z.B. 

> *int a = 10;*

`Zuweisung` Allgemeine Zuweisung eines Wertes, welches die Initialisierung sein, aber auch später stattfinden kann, z.B. 

> *int b = 9; 
> b = 10;*

**Unterschiede**
Jede Initialisierung ist eine Zuweisung, aber nicht jede Zuweisung eine Initialisierung. Die Initialisierung findet nur statt wird der Variable zum ersten Mal ein Wert zugewiesen.

## Aufgabe 1.6
`Deklaration` Man sagt dem Compiler, dass eine Funktion *(Signatur)*, Variable *(Typ und Name)*, Konstante oder Klasse existiert z.B.

> *int a;*
> *void test();*
> *class Test;*

`Definition` Macht die Details einer Entität bekannt, was bei Variablen dazu führt, dass Speicher reserviert wird.

> *a = 10;*
> *void test() { /\*Inhalt\*/ }*
> *class Test { /\*Inhalt\*/ };*

**Unterschiede**
Eine Deklaration gibt dem Compiler die Info, dass z.B. eine Variable oder Funktion existiert, während die Definition diesen dann einen Wert oder Inhalt zuordnet.

## Aufgabe 1.7
**Signatur:**
 `Rückgabetyp` *(oder void)* + `Name(Eingabeparameter)` 

![Aufgabenstellung](aufgabe_1_7.PNG)

> int var = 3; `global gültig`
> 
> **main()**
> i `gütig in for-Schleife`
> 
> **square(int var)** 
> var `lokal, nur gültig in square()`
> 
> **sum (double a, double b)** 
> a `lokal, nur gültig in sum()` 
> b `lokal, nur gültig in sum()`

## Aufgabe 1.16
- `C++` generische, imperative, objektorientierte, prozedurale, strukturierte, funktionale Programmiersprache; ursprünglich als Erweiterung von C gedacht
- `Quellcode` Abfolge von Anweisungen in einer höheren Programmiersprache, die von einem Computer verarbeitet werden 
- `Compiler` übersetzt Programmcode in Maschinensprache für den Prozessor 
- `Linker` Anzahl mehrerer Objektdateien generiert von einem Compiler, kombiniert zu einem einzelnen Programm 
- `Objektcode` Zwischenprodukt spezieller Art von Compilern; einzelne Module aus dem Quellcode werden zu maschinenlesbarem Code übersetzt und können dann von Linkern verbunden werden
- `Ausführbare Datei` kann als ein Computerprogramm ausgeführt werden 
- `main()` Startmethode eines C++ Programms 
- `#include` fügt andere Dateien in einen Quellcode ein, deren Inhalt nun einfach im Programm mitverwendet werden kann
- `Kommentar` werden nicht in Maschinensprache übersetzt und dienen als Hinweise, Beschreibungen und Erklärungen für das Verständnis der Programmierer 
- `Header`  Dateien der Endung *.h* oder *.hpp*, welche Funktionen und Variablen deklarieren, welche dann in der *.cpp* definiert werden
- `Programm` Serie von Anweisungen an einen Computer, damit dieser bestimmte Operationen ausführt
- `Ausgabe` Anzeigen des Ergebnisses eines ausgeführten Programmes z.B. über ein Terminal
- `std::cout` *std* ist Kurzform für standard; die Ausgabe-Methode *cout* ist im *std* namespace gespeichert; erzeugt einen Output im Terminal 
- `std::cin` ermöglicht eine Eingabe über die Konsole 
- `<<` Output-Operator
- `>>` Input-Operator
- `Funktion` Bezeichnung eines Programmkonstrukts; hilfreich zur Strukturierung des Quellcodes; darin vorhandener Code-Block kann über Methodenaufruf wiederverwendet werden
- `Funktionssignatur` deklariert eine Funktion mit Typ der Rückgabe, Namen der Funktion und den Eingabeparametern
- `Deklaration` macht eine Variable *(Datentyp + Name)* dem Compiler bekannt
- `Definition` teilt einer Variable oder Konstante einen Wert zu, oder einer Klasse und Funktion den Inhalt
- `Typ` gibt an von welchem Datentyp (Art) der Inhalt von einer Variable ist
- `Typkonvertierung` ein Datentyp wird in einem Programm in einen anderen umgewandelt z.B. 

> *int i = 1;  
> double j = i; // j = 1.0*

- `Variable` Charakteristik, Nummer oder Menge die erhöht oder verringert, verändert oder ausgetauscht werden kann, und mittels eines Namens im Programm referenziert werden kann
- `Name` mittels diesem wird die Variable im Code referenziert und auf ihren Inhalt zugegriffen
- `Wert` Inhalt einer Variable; ist einem Variablennamen zugeordnet ist 
- `Initialisierung` Erst-Zuweisung eines Wertes an eine Variable, kann während der Deklaration oder später passieren
- `Zuweisung` allgemeine Zuweisung eines Wertes, welches die Initialisierung sein, aber auch später stattfinden kann
- `const` Keyword um eine Konstante zu deklarieren, die, wenn einmal erstellt, nur noch gelesen und nicht mehr verändert werden kann
- `Gültigkeitsbereich` Bereich in dem eine Variable sichtbar ist und auf sie zugegriffen werden kann 

## Aufgabe 2.2
*Include guards* ist eine Technik mit welcher das mehrfache Einbinden eines Headers unterbunden wird. Werden die Header, z.B. *Vec2.hpp*, zweimal eingebunden, wird es Compilation Errors geben, da hier z.B. die struct  Vec2 zweifach definiert werden würde.

## Aufgabe 2.7
`struct` Konstrukte haben standardmäßig öffentliche Members und eignen sich als Datenstrukturen.

`class` Konstrukte standardmäßig private Members haben, und diese nach Konvention auch nicht zu public umgeformt, und nur per *get* abgerufen werden sollten! 

*Datentransferobjekte* oder auch *DTO* sind ein Entwurfsmuster, bei dem mehrere Daten / Methoden in einem Objekt gebündelt werden. Dann muss man das Objekt nur einmal aufrufen, um dann die Methoden zur Verfügung zu haben ohne weitere Fernzugriffe.

## Aufgabe 2.9
Nach dem C++ Standard existieren keine *Methoden*, obwohl dieser Begriff dennoch oft auswechselbar mit *Funktionen* verwendet wird.
Man könnte mit einer Methode Funktionen beschreiben, die abhängig von einem Objekt sind, währenddessen Funktionen allgemein auch global und allgemein gültig sein können.
Bei const-Member Methoden wird das Versprechen gegeben, dass das Objekt, auf dem sie aufgerufen werden, nicht verändert wird. Bei Funktionen die unabhängig von Objekten sind, bestimmt const je nach Anwendung über das Versprechen, das ein Rückgabewert oder Parameter nicht verändert werden darf.

## Aufgabe 2.12
Das *Überladen* von Funktionen, auch als *Overloading* bezeichnet, beschreibt das Definieren unterschiedlicher Funktionen mit gleichem Namen, aber unterschiedlichen Eingabeparametern. Hierbei wird beim Aufrufen die Funktion verwendet, die zu den Eingabeparametern passt. 

## Aufgabe 3.1
**Sequentielle Container** sind Container-Klassen, die Daten in einer Sequenz speichern. Hierbei wird entweder über einen numerischen Index, welcher die Stelle eines Wertes in der Sequenz beschreibt, oder durch das Wandern über andere Elemente auf den gesuchten Wert zugegriffen.
*Bsp.: array, vector, dequeue, list, ...*

**Assoziative Container** sind Container-Klassen die in Paaren aus Schlüssel und Wert speichern, wobei der Schlüssel die Position beschreibt, an welcher der Wert im Container gespeichert wird. Somit wird also über den Schlüssel auf den Wert zugegriffen.
*Bsp.: map, set  (value itself is the key), ...*

**Komplexität**
|  | Sequenz | Assoziativ |
|--|--|--|
| Insertion | Constant | O(log n) |
| Removal | Constant | O(log n) |
| Search | Constant | O(log n) |

- `Speichern der Punkte eines Polygons`
Hier bietet sich der *Sequentieller Container* z.B. ein *Array von Vektoren* an, da hier nicht standardmäßig nach Werten sortiert wird, und man die sequentielle Reihenfolge dazu nutzen kann um herauszufinden was der nächste Punkt ist zu dem man zeichnen muss von einem Punkt aus. 

- `Zuordnung von Farbnamen und entsprechenden RGB-Werten`
Hier bietet sich der *Assoziativer  Container* z.B. eine *Map* an, da man den Schlüssel für den Namen und den Wert für das RGB verwenden kann, und keine Duplikate zugelassen sind.

- `FIFO-Warteschlange von Druckaufträgen`
Hier bietet sich der *Sequentieller Container* z.B. eine *Queue* an, da man hier die Warteschlange bzw. Sequenz schön nacheinander abarbeiten kann. Die Reihenfolge muss man sich nicht merken, da sie schon in der Sequenz an sich gespeichert ist.

## Aufgabe 3.3
std::map is useful for this task, because it:
   - only has unique keys with one value mapped to it
   - sorts keys by default
   - searching for keys is very fast (logarithmic time)

## Aufgabe 3.5

**ORIGINAL**

    std :: map <string ,int > matrikelnummern ;
    // Hinzufuegen von vielen Studenten
    matrikelnummern ["Max Mustermann"] = 12345;
    matrikelnummern ["Erika Mustermann"] = 23523;
    // ...
    exmatrikulation (matrikelnummer["Fred Fuchs"]);

**FEHLER**

`std::map<string, int>` --> `std::map<std::string, int>`
`matrikelnummer["Fred Fuchs"]` --> `matrikelnummern["Fred Fuchs"]`

**PROBLEME**

- Keys lassen keine Duplikate zu, sollten also hier die Matrikelnummern sein, da doppelte Namen keine Seltenheit sind
- Übergabe von Matrikelnummer als Integer, `exmatrikulation()` hat möglicherweise keinen Zugriff auf die Map --> Fred Fuchs wird exmatrikuliert, bleibt in der Liste

**METHODEN**

*Einfügen eines Paars*

     a_map[key] = value;
     a_map.insert(std::make_pair(key, value));

*Entfernen von Paar*

    erase(e) // Entfernen per Key oder per Iterator (Element auf das dieser pointet)

    erase(it1,it2) // Entfernen von Elementen des in Range der Iteratoren it1 bis it2 - 1

*Finden eines Keys*

    wordMap.count(key) > 0 // Testet ob Key existiert mittels count()
    
    it = wordMap.find(key);
    it != wordMap.end() // Testet ob Key existiert mittels Iterator und find()

*Allgemeine Methoden*

`std::search` Suche erstes Aufkommen einer Zeichensequenz in der gegebenen Reichweite nach dem Kriterium

`std::find` Suche erstes Aufkommen eines Elementes in der gegebenen Reichweite nach dem Kriterium

`iterator` vs `const_iterator` Normale Iteratoren erlauben das Ändern der gefundenen Elemente, anders als const Iteratoren -> möglicherweise Problem

## Aufgabe 4.8

**DEEP-COPY**: - copy values, objects will be traversed and their values copied as well
**SHALLOW-COPY**: - copy only simple data types, copy references to objects / complex datatypes

**copy constructor is called when**:
- an object is returned by value
- an object of class is passed to a function by value
- an object is constructed based on another object of the same class
- the compiler generates a temporary object

**by default, C++ compiler creates its own default** copy constructor (shallow-copy)

**custom copy-constructor is needed**, if there are pointers or any runtime allocation, also allows for deep copy        

**Why copy-constructor pass by value?** -> copy constructor is a function in its basic form
that is always called when there is an argument pass by value ->
if not using reference in copy constructor -> infinite loop

## Aufgabe 4.14

Move Constructor??
auto l = List<int>{1,2,3,4,5} + List<int>{6,7,8,9};

## Task 5.3

- beim Erstellen des Sphere Objekts
- ruft den Konstruktor der Basisklasse (Shape) zuerst auf, dann den Konstruktor der abgeleiteten Klasse (Sphere)
- wenn der eine Initialisierungsliste existiert, konstruktor der basisklasse wird am Anfang der Liste aufgerufen
- Konstruktor der Basisklasse kann als Punkt in Liste (am Anfang) definiert werden e.g. Shape(), Shape(string name), ..

## Task 5.5

*override*
- stellt sicher, dass eine Funktion virtuell ist
- *falls dies nicht zutrifft: compile error*
- definiert, dass eine Klasse eine virtuelle Funktion seiner Basisklasse überschreibt (ersetzt)

## Task 5.7

**dynamic variable** 
- variable whose address is determined when the program is run

**static variable**
- already known at compilation time, has memory reseved for it at compilation time

*std::shared_ptr*
- smart pointer
- retains shared ownership of an object thrugh pointer
- several smart pointers may own the same object
- object is destroyed, when:
  - last smart pointer owning it is destroyed
  - last smart pointer owning it is assigned another pointer via = o. reset()
- can own object while storing pointer to another
  - for example, can be used to point to an object's member, while still owning the object

*std::make_shared*
- construct T object and wrap it in smart pointer

`std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>(position, 1.2f, red, "sphere0");`
- static pointer -> static pointer
  - in compilation-time known
  - can use all methods of sphere

`std::shared_ptr<Shape> s2 = std::make_shared<Sphere>(position, 1.2f, red, "sphere1");`
- static pointer -> to dynamic object
  - in run-time looks for Sphere object
  - can only run methods of Sphere (but virtual methods overriden by sphere still work)

## Task 5.8

*order of constructor / destructor calls*
1. constructor s1 (shape)
2. constructor s1 (sphere)
3. constructor s2 (shape)
4. constructor s2 (sphere)
5. destructor s1 (sphere)
6. destructor s1 (shape)
7. destructor s2 (sphere)
8. destructor s2 (shape)

on removing 'virtual' of base class 'shape' (and 'override' tags)
- destructor for sphere3 is called only once, since it's not linked with child class
- because:
  - shape -> sphere
  - shape delete -> calls size_of for size of object 
    - -> gets size of base class, because not virtual 
    - -> only deletes base object 

1. constructor s1 (shape)
2. constructor s1 (sphere)
3. constructor s2 (shape)
4. constructor s2 (sphere)
5. destructor s1 (sphere)
6. destructor s1 (shape)
7. destructor s2 (shape)

## Task 5.9

**Klassenhierarchie**
- baumartige Struktur
- ist Beziehung zwischen Klassen dar (Basisklasse und abgeleitete Klassen)

**Objekthierarchie**
- Relationen (Ordnung, Komposition) der Objekte in einem System (Geschwister, Eltern, Kinder, usw..)

**Klassendiagramm**
- zeigt statische Struktur eines Systems in Diagram Form
- allgemein: Klassennamen, Attribute, Relation zwischen Klassen

**Objektdiagramm**
- stellt alle Objekte eines Systems mit ihren Relationen (Ordnung, Komposition) dar
- mehrere Objekte einer Klasse möglich
- Objektname, Klassennamen, Klassenattribute mit zugewiesenen Werten, Relation zu anderen Objekten (Geschwister, Eltern, Kinder, usw..)

## Task 6.1

```c++
void raycast()
	for all pixels(x,y)
		image(x,y) = trace( compute_eye_ray(x,y) )
```

→ go through each pixel of image<br />
→ send out ray<br />
→ get pixel array<br />
→ convert to image and display<br />

```c++
rgbColor trace(ray r)
	for all objects o
		t = compute_intersection(r, o)
		if (t < closest_t)
			closest_t = t
			closest_o= o
		if (closest_o != 0)
			return shade(closest_o, r, closest_t)
		else
			return background_color
```

→ compute intersection for all objects<br />
→ if no object found: return background color<br />
→ if object(s) found: find closest object<br />
→ compute shade on pixel and return color<br />

```c++
rgbColor shade(object o, ray r, double t)
	point x = r(t)
	// evaluate(Phong) illumination equation
	return color
```

→ send out ray from intersection to point light nodes<br />
→ compute lighting using Phong and ambient and point lights<br />
→ return light-influenced color for pixel<br />
<br />
<br />
<br />
**Missing: reflection**<br />
→ shootout rays from intersection with light reflection angle<br />
→ if ray hits object, return object color →  send new ray (infinitely)<br />
→ if ray reaches max depth, return background color<br />
→ use calculated distance and apply color with a factor to first object