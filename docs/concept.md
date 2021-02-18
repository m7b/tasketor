### Tabelle `tPeriode`
Wiederholungsperiode / Bindungsperiode

| cId | cPeriode      | cDescription |
|-----|---------------|--------------|
|   1 | einmalig      |              |
|   2 | jedes mal     |              |
|   3 | täglich       |              |
|   4 | wöchentlich   |              |
|   5 | 2-wöchentlich |              |
|   6 | monatlich     |              |


### Tabelle `tEvent`
Events

| cId | cEvent | cEventDetails | cFirstTime | cPeriodeId (Wiederholungsperiode) | cWeekdays              |
|-----|--------|---------------|------------|-----------------------------------|------------------------|
|   1 | Ev-A   |  9:30 -  9:45 | 2020-10-01 | täglich                           | Mo, Di, Mi, Do, Fr, Sa |
|   2 | Ev-B   | 19:15 - 21:00 | 2020-10-07 | wöchentlich                       | Mi                     |
|   3 | Ev-C   | 18:30 - 20:15 | 2020-10-03 | wöchentlich                       | Sa                     |


### Tabelle `tEventReplacementPlan`
Ausfall-/Ersatzplan für Events

| cId | cEventId  | cPlan      | cReplacement | cReason                |
|-----|-----------|------------|--------------|------------------------|
|   1 |       1   | 21.10.2020 | 20.10.2020   | Außerplanmäßiger Grund |
|   2 |       2   | 14.11.2020 | <entfällt>   | Außerplanmäßiger Grund |


### Tabelle `tTask`
Aufgaben für alle Events

| cId | cTask  | cDescription  | cPeriodeId (Bindungsperiode) |
|-----|--------|---------------|------------------------------|
|   1 | Ta-A   | Host          | Jedes mal                    |
|   2 | Ta-B   | Co-Host       | Jedes mal                    |
|   3 | Ta-C   | Vorsitz       | Jedes mal                    |
|   4 | Ta-D   | Leser         | Jedes mal                    |
|   5 | Ta-E   | Host TP       | Jedes mal                    |


### Tabelle `tEventTasks`
Zuteilung der Aufgaben zu den Events

| cId | cEventId | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E |
|-----|----------|------|------|------|------|------|
|   1 | Ev-A     |      |      |      |      |   X  |
|   2 | Ev-B     |   X  |   X  |      |      |      |
|   3 | Ev-C     |   X  |   X  |   X  |   X  |      |

Evtl. bessere Darstellung

| cId | cEventId | cTaskId |
|-----|----------|---------|
|   1 | Ev-A     | Ta-E    |
|   2 | Ev-B     | Ta-A    |
|   3 | Ev-B     | Ta-B    |
|   4 | Ev-C     | Ta-A    |
|   5 | Ev-C     | Ta-B    |
|   6 | Ev-C     | Ta-C    |
|   7 | Ev-C     | Ta-D    |


### Tabelle `tTaskMatrix`
Aufgabenmatrix, welche Aufgaben gleichzeizig zugewiesen werden können

| Ta/Ta | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E |
|-------|------|------|------|------|------|
| Ta-A  |   X  |      |      |      |      |
| Ta-B  |      |   X  |   X  |   X  |      |
| Ta-C  |      |   X  |   X  |      |      |
| Ta-D  |      |   X  |      |   X  |      |
| Ta-E  |      |      |      |      |   X  |

Evtl. bessere Darstellung

| cId | cTaskId | cTaskId_atst |
|-----|---------|--------------|
|   1 | Ta-B    | Ta-C         |
|   2 | Ta-B    | Ta-D         |
|   3 | Ta-C    | Ta-B         |
|   4 | Ta-D    | Ta-B         |

atst = at the same time


### Tabelle `tPerson`
Personen die zu Aufgaben eingeteilt werden können

| cId | cName     |
|-----|-----------|
|   1 | Edgar     |
|   2 | Eber      |
|   3 | Braftaler |
|   4 | Burbs     |
|   5 | Grumml    |
|   6 | Eufers    |
|   7 | Siffel    |


### Tabelle `tTaskAssign`
Wer kann welche Aufgaben durchführen/übernehmen

| Person    | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E |
|-----------|------|------|------|------|------|
| Edgar     |   X  |   X  |   X  |   X  |      |
| Eber      |      |   X  |      |   X  |      |
| Braftaler |   X  |   X  |   X  |   X  |   X  |
| Burbs     |   X  |   X  |   X  |   X  |      |
| Grumml    |      |      |      |   X  |   X  |
| Eufers    |      |      |   X  |   X  |      |
| Siffel    |      |      |   X  |   X  |      |

Evtl. bessere Darstellung

| cId | cPersonId | cTaskId |
|-----|-----------|---------|
|   1 | Edgar     | Ta-A    |
|   2 | Edgar     | Ta-B    |
|   3 | Edgar     | Ta-C    |
|   4 | Edgar     | Ta-D    |
|   5 | Eber      | Ta-B    |
|   6 | Eber      | Ta-D    |
|   7 | Braftaler | Ta-A    |
|   8 | Braftaler | Ta-B    |
|   9 | Braftaler | Ta-C    |
|  10 | Braftaler | Ta-D    |
|  11 | Braftaler | Ta-E    |
|  12 | Burbs     | Ta-A    |
|  13 | Burbs     | Ta-B    |
|  14 | Burbs     | Ta-C    |
|  15 | Burbs     | Ta-D    |
|  16 | Grumml    | Ta-D    |
|  17 | Grumml    | Ta-E    |
|  18 | Eufers    | Ta-C    |
|  19 | Eufers    | Ta-D    |
|  20 | Siffel    | Ta-C    |
|  21 | Siffel    | Ta-D    |


### Tabelle `tPersonAbsent`
Abwesenheitsliste der Personen

| cId | cPersonId | cFrom      | cTo        |
|-----|-----------|------------|------------|
|   1 | Edgar     | 26.10.2020 | 01.11.2020 |
|   2 | Braftaler | 31.10.2020 |            |


### Grober Ablauf für die Erstellung der Aufgabenliste

Erstelle Planung <von Datum> <bis Datum>

 1. Füge planmäßige Events in Kalender
 2. Verändere planmäßige Events in Kalender unter Berücksichtigung eines Ersatztermins
 3. Erstelle Spaltenanordnung der Tasks.
    - Task mit größte Bindungsperiode ganz links.
	- Abnehmende Bindungsperiode nach rechts anordnen.
 3. Erstelle Liste mit anwesenden Personen je Event
 4. Zuweisung Personen zu den Aufgaben zu jedem Event