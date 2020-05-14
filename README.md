# gravesite-beaconing
<b>IoT-Sp-2020-Final</b>

README, directory listing and setup instructions

<b>Important Links:</b>
The video detailing process and demonstrating the parts for this project can be found here : <a href="https://drive.google.com/file/d/155o_H0zbMqdDoUw9AnUA0LflL79hAfPu/view?usp=sharing"> link.</a>
The report documenting and detailing the process of this project can be found here : <a href = "https://docs.google.com/document/d/17jf9HsJg-zgWmgU-BfE7ktTV50ADjPDQareK2d50IZs/edit?usp=sharing"> link.</a>


<b> FILE AND DIRECTORY LISTING:</b>

-3D models: the repository of the yet untested 3D models associated with this project 

-beacon code : the code for the arduino nanos running the beacons. v4 is currently deployed 

	the current version is v4

-beacon coordinator code : code for the beacon coordinator xbee .currently turns on beacon by pot input not web input :-I

	the current version is v2

-diagrams : high resolution wiring diagrams from the paper 

-Final Scratch Work : assorted debris, backups and experimental runs from the course of the project

	only noteworthy items listed 

	nameNplotNcoord.csv : the working source for information on individual gravesites. 

	csvtojson.py : takes the input data from the source csv and converts it to geoJSON input for the web

	all html here are drafts from experimentation 

-google cloud deployed assets : currently, the cloud function index.js and package.json triggers by firestore write are here 

-required 3rd party libraries: used in the creation of the beacon coordinator

	arduino-mqtt and google-cloud-iot-arduino 

-WebPortal : source for what is served here : https://www.stjosephcemeterybr.org/ 

	bigmap.png : the aptly named source for the map overlay

	graves.json : generated from csv records. read in to map for point locations

	index.html : pulls it all together to generate and draw the map.

-Final Report.pdf - a copy of the submitted final report 

-XBee config : the configuration information for the beacon and beacon coordinator XBees
