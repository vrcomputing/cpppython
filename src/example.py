# filter module with global functions
import pyfiltermodule
# filter module with actual filter object
import pyfilter
# pip install requests
import requests

def process_input(pin_name):

	# create an instance of pyfilter.Filter
	filter = pyfilter.Filter()

	if pyfiltermodule.create_input_pin("a"):
		print("success")

	if pyfiltermodule.create_output_pin("b"):
		print("success")

	if filter.set_property("x", 1):
		print(filter.get_property("y"))

	return 1.337

def process(runner_name):
	print(runner_name)
	r = requests.get('https://xkcd.com/1906/')	
	return r.text