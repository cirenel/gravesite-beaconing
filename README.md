# gravesite-beaconing
IoT-Sp-2020-Final

FILE and DIRECTORY LISTING:

-3D models: the repository of the yet untested 3D models associated with this project 

-beacon code : the code for the arduino nanos running the beacons. 

	the current version is v4
	
	previous incarnations included with comments to their specefics

-beacon coordinator code : code for the beacon coordinator esp32 and xbee. currently turns on beacon through web input

	the current version is v2
	
	previous incarnations included with comments to their specefics

-diagrams : high resolution wiring diagrams from the paper 

-Final Scratch Work : assorted debris, backups and experimental runs from the course of the project

	only noteworthy items listed 

	nameNplotNcoord.csv : the working source for information on individual gravesites. 

	csvtojson.py : takes the input data from the source csv and converts it to geoJSON input for the web

	all html here are drafts from experimentation 

-google cloud deployed assets : currently, the cloud function index.js and package.json triggers by firestore write are here 

-required 3rd party libraries: used in the creation of the beacon coordinator

	arduino-mqtt 
	
	google-cloud-iot-arduino 

-WebPortal : source for what is served here : https://www.stjosephcemeterybr.org/ 

	bigmap.png : the aptly named source for the map overlay

	graves.json : generated from csv records. read in to map for point locations

	index.html : pulls it all together to generate and draw the map.

-Final Report.pdf - a copy of the submitted final report 

-XBee config : the configuration information for the beacon and beacon coordinator XBees
