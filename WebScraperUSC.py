import requests
import sys
from bs4 import BeautifulSoup 
def get_HTML_code(major, number):
	url = 'https://classes.usc.edu/term-20201/course/' + major + "-" + number + "/"
	return requests.get(url).text

def GetClasses(major, number):

	source = get_HTML_code(major, number)
	soup = BeautifulSoup(source, "html.parser") #Does html parsing. 
	table = soup.find('table')
	

	filename = major + number + ".csv"
	f = open(filename, "w")

	count = 0
	for section in table.find_all('tr'):
		#count+=1
		#if count == 1:
		#	continue
		if not section.has_attr("data-section-id"):
			continue
		Section = section["data-section-id"]
		Session = section.find('td', {"class":"session"}).text
		Type = section.find('td', {"class":"type"}).text
		Time = section.find('td', {"class":"time"}).text
		Days = section.find('td', {"class":"days"}).text
		Registered = section.find('td', {"class":"registered"}).text
		Instructor = section.find('td', {"class":"instructor"}).text
		if section.find('td', {"class":"location"}).text == "TBA":
			Location_Building = "TBA"
			Location_Room = "TBA"
		else:
		#	Location_Building  = section.find('td', {"class":"location"}).a.text
			Location_Room = section.find('td', {"class":"location"}).text

		f.write(Section + "," + Session + "," + 
			Type + "," + Time +
			"," + Days.replace(","," ") + "," + 
			Registered.replace(" of ",",") + "," + Instructor.replace(","," & ") +
			 "," + Location_Room + "\n")
		#.replace(xyz) will repalce 

	f.close()

#GetClasses("csci", "103")
def main():
	# major_name = argv[1]
	# major_code = argv[2]
	GetClasses(sys.argv[1], sys.argv[2])

if __name__ == '__main__':
	main()




