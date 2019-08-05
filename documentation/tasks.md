
# Programmiersprachen 5

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