### Tabelle `tEvents`
Events

| cId | cEvent | cEventDetails | cRepeat       | cWeekdays              |
|-----|--------|---------------|---------------|------------------------|
|   0 | Ev-A   |  9:30 -  9:45 | Täglich       | Mo, Di, Mi, Do, Fr, Sa |
|   1 | Ev-B   | 19:15 - 21:00 | Wöchentlich   | Mi                     |
|   2 | Ev-C   | 18:30 - 20:15 | Wöchentlich   | Sa                     |


### Tabelle `tEventReplacementPlan`
Ausfall-/Ersatzplan für Events

| cId | cEventId  | cPlan      | cReplacement | cReason                |
|-----|-----------|------------|--------------|------------------------|
|   0 |       1   | 21.10.2020 | 20.10.2020   | Außerplanmäßiger Grund |
|   1 |       2   | 14.11.2020 | <entfällt>   | Außerplanmäßiger Grund |


### Tabelle `tTasks`
Aufgaben für alle Events

| cId | cTask  | cDescription  | cPeriodId (Personenbindung) |
|-----|--------|---------------|-----------------------------|
|   0 | Ta-A   | Host          | Jedes mal                   |
|   1 | Ta-B   | Co-Host       | Jedes mal                   |
|   2 | Ta-C   | Vorsitz       | Jedes mal                   |
|   3 | Ta-D   | Leser         | Jedes mal                   |
|   4 | Ta-E   | Host TP       | Jedes mal                   |


### Tabelle `tCommitmentPeriod`
Die Personenbindung einer Aufgabe

| cId | cPeriod       | cDescription |
|-----|---------------|--------------|
|   0 | Jedes mal     |              |
|   1 | täglich       |              |
|   2 | wöchentlich   |              |
|   3 | 2-wöchentlich |              |
|   4 | monatlich     |              |


### Tabelle `tEventTasks`
Zuteilung der Aufgaben zu den Events

| cId | cEventId | Ta-A | Ta-B | Ta-C | Ta-D | Ta-E |
|-----|----------|------|------|------|------|------|
|   0 | Ev-A     |      |      |      |      |   X  |
|   1 | Ev-B     |   X  |   X  |      |      |      |
|   2 | Ev-C     |   X  |   X  |   X  |   X  |      |

Evtl. bessere Darstellung

| cId | cEventId | cTaskId |
|-----|----------|---------|
|   0 | Ev-A     | Ta-E    |
|   1 | Ev-B     | Ta-A    |
|   2 | Ev-B     | Ta-B    |
|   3 | Ev-C     | Ta-A    |
|   4 | Ev-C     | Ta-B    |
|   5 | Ev-C     | Ta-C    |
|   6 | Ev-C     | Ta-D    |


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
|   0 | Ta-B    | Ta-C         |
|   1 | Ta-B    | Ta-D         |
|   2 | Ta-C    | Ta-B         |
|   3 | Ta-D    | Ta-B         |

atst = at the same time


### Tabelle `tPerson`
Personen die zu Aufgaben eingeteilt werden können

| cId | cName     |
|-----|-----------|
|   0 | Edgar     |
|   1 | Eber      |
|   2 | Braftaler |
|   3 | Burbs     |
|   4 | Grumml    |
|   5 | Eufers    |
|   6 | Siffel    |


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
|   0 | Edgar     | Ta-A    |
|   1 | Edgar     | Ta-B    |
|   2 | Edgar     | Ta-C    |
|   3 | Edgar     | Ta-D    |
|   4 | Eber      | Ta-B    |
|   5 | Eber      | Ta-D    |
|   5 | Braftaler | Ta-A    |
|   6 | Braftaler | Ta-B    |
|   7 | Braftaler | Ta-C    |
|   8 | Braftaler | Ta-D    |
|   9 | Braftaler | Ta-E    |
|  10 | Burbs     | Ta-A    |
|  11 | Burbs     | Ta-B    |
|  12 | Burbs     | Ta-C    |
|  13 | Burbs     | Ta-D    |
|  14 | Grumml    | Ta-D    |
|  15 | Grumml    | Ta-E    |
|  16 | Eufers    | Ta-C    |
|  17 | Eufers    | Ta-D    |
|  18 | Siffel    | Ta-C    |
|  19 | Siffel    | Ta-D    |


### Tabelle `tPersonAbsent`
Abwesenheitsliste der Personen

| cId | cPersonId | Abwesenheit von | Abwesenheit bis |
|-----|-----------|-----------------|-----------------|
|   0 | Edgar     | 26.10.2020      | 01.11.2020      |
|   1 | Braftaler | 31.10.2020      |                 |


### Grober Ablauf für die Erstellung der Aufgabenliste

Erstelle Planung <von Datum> <bis Datum>

 1. Füge planmäßige Events in Kalender
 2. Verändere planmäßige Events in Kalender unter Berücksichtigung eines Ersatztermins
 3. Erstelle Spaltenanordnung der Tasks.
    - Task mit größte Personenbindung ganz links.
	- Abnehmende Personenbindung nach rechts anordnen.
 3. Erstelle Liste mit anwesenden Personen je Event
 4. Zuweisung Personen zu den Aufgaben zu jedem Event