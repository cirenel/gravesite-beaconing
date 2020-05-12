# gravesite-beaconing
IoT-Sp-2020-Final

README, directory listing and setup instructions

DIRECTORY LISTING:
WebPortal : source for what is served here : https://www.stjosephcemeterybr.org/ 
	bigmap.png : the aptly named source for the map overlay
	graves.json : generated from csv records. read in to map for point locations
	index.html : pulls it all together to generate and draw the map.

beacon code : the code for the arduino nanos running the beacons. v4 is currently deployed 

beacon coordinator code : code for the beacon coordinator xbee .currently turns on beacon by pot input not web input :-I

Final Scratch Work : assorted debris, backups and experimental runs from the course of the project
	only noteworthy items listed 
	nameNplotNcoord.csv : the working source for information on individual gravesites. 
	csvtojson.py : takes the input data from the source csv and converts it to geoJSON input for the web
	all html here are drafts from experimentation 
	
