
# Programmiersprachen 5

## Aufgabe 5.3

- beim Erstellen des Sphere Objekts
--> ruft den Konstruktor der Basisklasse (Shape) zuerst auf, dann den Konstruktor der abgeleiteten Klasse (Sphere)

## Aufgabe 5.5

*override*
- stellt sicher, dass eine Funktion virtuell ist
- *falls dies nicht zutrifft: compile error*
- definiert, dass eine Klasse eine virtuelle Funktion seiner Basisklasse überschreibt (ersetzt)

## Aufgabe 5.7

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
  - for exammple, can be used to point to an object's member, while still owning the object

*std::make_shared*
- construct T object and wrap it in smart pointer

## Aufgabe 5.8

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
destructor for sphere3 is called only once, since it's not linked with child class

1. constructor s1 (shape)
2. constructor s1 (sphere)
3. constructor s2 (shape)
4. constructor s2 (sphere)
5. destructor s1 (sphere)
6. destructor s1 (shape)
7. destructor s2 (shape)

## Aufgabe 5.9

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
