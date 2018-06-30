//InfoCardExample.cpp by Konstantine Kozachuck as neurocod - 2018.06.30 17:59:03
#include "pch.h"
#include "InfoCardExample.h"

const QString InfoCardExample::example =
R"DEMO(#!info:10b0085be05e167d:75026577fafe0aff372db9846805c8
#
# This is example of personal card for emerCoin Info system
# This card will be retrieved by reference to NVS from EMCSSL subsystem.
#
# All fields are OPTIONAL
#
# Syntax:
# Keyword (whitespaces) value
# If keyword is omitted, value will be added as additional element
# into values list, reference by this keyword (see HomeAddress following).
#
# Card can contain reference to "parent" card(s) with syntax like:
# Import info:569dcc6b7aee11375b76:62615c3f6f62096b68bbc980c153917d505f8d24	
#
# By default, value(s) from current INFO file overwrite values from parent's one
# To change merging behavior, use qualifiers at keyword:
# KeyWord+	- Parent's list will be added after current list
# +KeyWord	- Parent's list will be added before current list
# KeyWord with no params - clear this value from resulting card
#
# 
#
Alias		superabdul			# Short name (username, login)
FirstName	Abdul				# First (short) name
LastName	Kurbashi Bey			# Remain part of full name
HomeAddress
	Sinan Pasa Mah. Hayrettin Iskelesi	# Free form address
	Sok. No \#1				# Free form address 
	Besiktas, Besiktas			# Free form address
	Istanbul				# City
	34353					# ZIP code
	Turkey					# Country
HomePhone	+90-555-123-4567
WorkPhone	+90-555-123-4568
CellPhone	+90-555-123-4569
Gender		M
Birthdate	1991-05-27			# May, 27, 1991
Email		abdul@bubbleinflators.com
WEB		http://www.bubbleinflators.com/superabdul
Facebook	Abdul.KurbashiBey
Twitter		AbdulKurbashiBey
EMC	EdvJ7b7zPL6gj5f8VNfX6zmVcftb35sKX2	# EmerCoin payment address
BTC	1MkKuU78bikC2ACLspofQZnNb6Vz9AP1Np	# BitCoin payment address
)DEMO";
//_____________________________________________
const QString InfoCardExample::corporate =
R"DEMO(#
# This is example of corp InfoCard for EmerCoin Info system
# This card will be retrieved by reference to NVS from EMCSSL subsystem,
# or imported by another card.
#
# All fields are OPTIONAL
#
# Syntax:
# Keyword (whitespaces) value
# If keyword is omitted, value will be added as additional element
# into values list, reference by this keyword (see HomeAddress following).
#
# Card can contain reference to "parent" card(s) with syntax like:
# Import info:569dcc6b7aee11375b76:62615c3f6f62096b68bbc980c153917d505f8d24	
#
# By default, value(s) from current INFO file overwrite values from parent's one
# To change merging behavior, use qualifiers at keyword:
# KeyWord+	- Parent's list will be added after current list
# +KeyWord	- Parent's list will be added before current list
# KeyWord with no params - clear this value from resulting card
#
# 
#
BusinessAddress
	Kucuk Ayasofya Cad. Kapi Agasi		# Free form address
	Sok. No:55				# Free form address 
	Sultanahmet, Fatih			# Free form address
	Istanbul				# City
	34400					# ZIP code
	Turkey					# Country
WorkPhone	+90-555-123-4568
Email		info@bubbleinflators.com
WEB		http://www.bubbleinflators.com
Facebook	BubbleInflators
Twitter		BubbleInflators
)DEMO";
//_____________________________________________
const QString InfoCardExample::user =
R"DEMO(#!info:2eb9b3d01cd8315e:4c325ce03128150fb831d34c663136
#
# This is example of personal card for emerCoin Info system
# This card will be retrieved by reference to NVS from EMCSSL subsystem.
#
# All fields are OPTIONAL
#
# Syntax:
# Keyword (whitespaces) value
# If keyword is omitted, value will be added as additional element
# into values list, reference by this keyword (see HomeAddress following).
#
# Card can contain reference to "parent" card(s) with syntax like:
# Import info:569dcc6b7aee11375b76:62615c3f6f62096b68bbc980c153917d505f8d24	
#
# By default, value(s) from current INFO file overwrite values from parent's one
# To change merging behavior, use qualifiers at keyword:
# KeyWord+	- Parent's list will be added after current list
# +KeyWord	- Parent's list will be added before current list
# KeyWord with no params - clear this value from resulting card
#
# 
#
Import		info:de4190d91886046e:e8d6726e73a6079d5ef8d6c3bf5858

Alias		superabdul			# Short name (username, login)
FirstName	Abdul				# First (short) name
LastName	Kurbashi Bey			# Remain part of full name
HomeAddress
	Sinan Pasa Mah. Hayrettin Iskelesi	# Free form address
	Sok. No \#1				# Free form address 
	Besiktas, Besiktas			# Free form address
	Istanbul				# City
	34353					# ZIP code
	Turkey					# Country
HomePhone	+90-555-123-4567
CellPhone	+90-555-123-4569
Gender		M
Birthdate	1991-05-27			# May, 27, 1991
Email+		abdul@bubbleinflators.com
+WEB		http://www.bubbleinflators.com/superabdul
Facebook	Abdul.KurbashiBey
Twitter		AbdulKurbashiBey
EMC	EdvJ7b7zPL6gj5f8VNfX6zmVcftb35sKX2	# EmerCoin payment address
BTC	1MkKuU78bikC2ACLspofQZnNb6Vz9AP1Np	# BitCoin payment address

)DEMO";