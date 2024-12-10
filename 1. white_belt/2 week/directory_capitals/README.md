### Programming task: Directory of capitals 

Implement a directory of country capitals.

The program receives the following requests:

* **CHANGE_CAPITAL *country new_capital*** - changing the capital of the country ***country*** to ***new_capital***, or adding such a country with such a capital, if it did not exist before.
* **RENAME *old_country_name new_country_name*** - rename country from ***old_country_name*** to ***new_country_name***.
* **ABOUT *country*** - displays the capital of the country ***country***.
* **DUMP** - displays the capitals of all countries.

### Input format 
The first line contains the number of queries *Q*, the next *Q* lines contain the descriptions of the queries. All names of countries and capitals consist only of Latin letters, numbers and underscores.

### Output format 
Print the result of processing each request:

In response to the query **CHANGE_CAPITAL *country* *new_capital*** print

* **Introduce new country *country* with capital *new_capital*** if ***country*** did not exist before;
* **Country *country* hasn't changed its capital** if country ***country*** had capital ***new_capital*** until now;
* **Country *country* has changed its capital from *old_capital* to *new_capital***, if the country ***country*** until now had a capital ***old_capital*** whose name does not match the name ***new_capital***.


In response to the query **RENAME *old_country_name* *new_country_name*** print

* **Incorrect rename, skip** if the new country name is the same as the old one, country ***old_country_name*** does not exist or country ***new_country_name*** already exists;
* **Country *old_country_name* with capital *capital* has been renamed to *new_country_name*** if the query is valid and the country's capital is ***capital***.

In response to the query **ABOUT *country*** print

* **Country *country* doesn't exist** if no country named ***country*** exists;
* **Country *country* has capital *capital*** if country ***country*** exists and has capital ***capital***.

In response to the **DUMP** prompt, output

* **There are no countries in the world** if no countries have been added yet;
* space-separated ***country/capital*** pairs describing the capitals of all countries and sorted by country name if there is already at least one country in the world.

### Example 1 
**Input**
```objectivec
6
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
ABOUT RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
DUMP
```

**Output**
```objectivec
Introduce new country RussianEmpire with capital Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic has capital Petrograd
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
USSR/Moscow
```
### Example 2 
**Input**
```objectivec
RENAME FakeCountry FarFarAway
ABOUT FarFarAway
DUMP
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL TsardomOfRussia Moscow
CHANGE_CAPITAL ColonialBrazil Salvador
CHANGE_CAPITAL TsardomOfRussia SaintPetersburg
RENAME TsardomOfRussia RussianEmpire
CHANGE_CAPITAL RussianEmpire Moscow
CHANGE_CAPITAL RussianEmpire SaintPetersburg
CHANGE_CAPITAL ColonialBrazil RioDeJaneiro
DUMP
RENAME ColonialBrazil EmpireOfBrazil
ABOUT RussianEmpire
RENAME EmpireOfBrazil UnitedStatesOfBrazil
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME RussianEmpire RussianRepublic
RENAME RussianRepublic USSR
CHANGE_CAPITAL USSR Moscow
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME UnitedStatesOfBrazil FederativeRepublicOfBrazil
ABOUT RussianEmpire
DUMP
RENAME USSR USSR
```

**Output**
```objectivec
Incorrect rename, skip
Country FarFarAway doesn't exist
There are no countries in the world
Introduce new country TsardomOfRussia with capital Moscow
Country TsardomOfRussia hasn't changed its capital
Introduce new country ColonialBrazil with capital Salvador
Country TsardomOfRussia has changed its capital from Moscow to SaintPetersburg
Country TsardomOfRussia with capital SaintPetersburg has been renamed to RussianEmpire
Country RussianEmpire has changed its capital from SaintPetersburg to Moscow
Country RussianEmpire has changed its capital from Moscow to SaintPetersburg
Country ColonialBrazil has changed its capital from Salvador to RioDeJaneiro
ColonialBrazil/RioDeJaneiro RussianEmpire/SaintPetersburg
Country ColonialBrazil with capital RioDeJaneiro has been renamed to EmpireOfBrazil
Country RussianEmpire has capital SaintPetersburg
Country EmpireOfBrazil with capital RioDeJaneiro has been renamed to UnitedStatesOfBrazil
Country RussianEmpire has changed its capital from SaintPetersburg to Petrograd
Country RussianEmpire with capital Petrograd has been renamed to RussianRepublic
Country RussianRepublic with capital Petrograd has been renamed to USSR
Country USSR has changed its capital from Petrograd to Moscow
Country UnitedStatesOfBrazil has changed its capital from RioDeJaneiro to Brasilia
Country UnitedStatesOfBrazil with capital Brasilia has been renamed to FederativeRepublicOfBrazil
Country RussianEmpire doesn't exist
FederativeRepublicOfBrazil/Brasilia USSR/Moscow
Incorrect rename, skip
```

### Example 3 
**Input**
```objectivec
10
CHANGE_CAPITAL RussianEmpire Petrograd
RENAME USSR RussianEmpire
DUMP
ABOUT USSR
DUMP
RENAME RussianEmpire RussianEmpire
DUMP
CHANGE_CAPITAL UnitedStatesOfBrazil Brasilia
RENAME RussianEmpire UnitedStatesOfBrazil
DUMP
```

**Output**
```objectivec
Introduce new country RussianEmpire with capital Petrograd
Incorrect rename, skip
RussianEmpire/Petrograd
Country USSR doesn't exist
RussianEmpire/Petrograd
Incorrect rename, skip
RussianEmpire/Petrograd
Introduce new country UnitedStatesOfBrazil with capital Brasilia
Incorrect rename, skip
RussianEmpire/Petrograd UnitedStatesOfBrazil/Brasilia
```
