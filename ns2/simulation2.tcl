set ns [new Simulator]

#Getting user input 
if { $argc != 2 } {
        puts "Error in syntax \n Try as shown \n."    
	puts "ns2.tcl <DROPTAIL or RED> <Senario No 1 or 2>\n"
	puts "Please try again \n"
    }
set Mech [lindex $argv 0]
set Scenario_No [lindex $argv 1]
global Mechanism Scenario_No

if { $Scenario_No <1 || $Scenario_No>2} {
puts "Sorry Please try again with a sequence number 1 or 2"
}

if { $Mech == "DROPTAIL" } {
	set Mechanism "DropTail"
	} elseif {$Mech == "RED"} {
	set Mechanism "RED"
} else {
	puts "Invalid Queue Mechanism"
	exit
}

#Tracing
set nf [open tcp.nam w]
$ns namtrace-all $nf

set f0 [open th1.tr w]
set f1 [open th2.tr w]
if { $Scenario_No == 2} {
set f2 [open th3.tr w]
}

#Initializing variables
set throughput1 0
set throughput2 0
set throughput3 0

#create network topology
set H1 [$ns node]
set H2 [$ns node]
set R1 [$ns node]
set R2 [$ns node]
set H3 [$ns node]
set H4 [$ns node]

if { $Scenario_No == 2} {
	set H5 [$ns node]
	set H6 [$ns node]
}

#Define colors for flow of data
$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green

#Create links
$ns duplex-link $H1 $R1 10.0Mb 1ms $Mechanism
$ns duplex-link $H2 $R1 10.0Mb 1ms $Mechanism
$ns duplex-link $R1 $R2 1.0Mb 10ms $Mechanism
$ns duplex-link $R2 $H3 10.0Mb 1ms $Mechanism
$ns duplex-link $R2 $H4 10.0Mb 1ms $Mechanism

if { $Scenario_No == 2} {
	$ns duplex-link $H5 $R1 10.0Mb 1ms $Mechanism
	$ns duplex-link $R2 $H6 10.0Mb 1ms $Mechanism
	}

$ns duplex-link-op $H1 $R1 orient right-down
$ns duplex-link-op $H2 $R1 orient right
$ns duplex-link-op $R1 $R2 orient right
$ns duplex-link-op $R2 $H3 orient right-up
$ns duplex-link-op $R2 $H4 orient right

if { $Scenario_No == 2} {
	$ns duplex-link-op $H5 $R1 orient right-up
	$ns duplex-link-op $R2 $H6 orient right-down
	}

$ns queue-limit $R1 $R2 20

if { $Mechanism == "RED"} {
	Queue/RED set thresh_ 10
	Queue/RED set maxthresh_ 15
	Queue/RED set linterm_ 50
}

#Setting up TCP 
set tcp1 [new Agent/TCP/Reno]
set tcp2 [new Agent/TCP/Reno]
set sink1 [new Agent/TCPSink]
set sink2 [new Agent/TCPSink]
$tcp1 set class_ 1
$tcp2 set class_ 2
$ns attach-agent $H1 $tcp1
$ns attach-agent $H3 $sink1
$ns attach-agent $H2 $tcp2
$ns attach-agent $H4 $sink2
$ns connect $tcp1 $sink1
$ns connect $tcp2 $sink2

#Setting FTP over TCP
set ftp1 [new Application/FTP]
set ftp2 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp2 attach-agent $tcp2

if { $Scenario_No == 2} {
	set udp_1 [new Agent/UDP]
	set sink3 [new Agent/LossMonitor]
	$ns attach-agent $H5 $udp_1
	$ns attach-agent $H6 $sink3
	$ns connect $udp_1 $sink3
	
	set cbr_1 [new Application/Traffic/CBR]
	$cbr_1 set packetSize_ 100
	$cbr_1 set rate_ 1Mb
	$cbr_1 attach-agent $udp_1
	
}

#Creating Record
proc record {} {
	global sink1 sink2 sink3 throughput1 throughput2 throughput3 Scenario_No f0 f1 f2
	set ns [Simulator instance]
	set time 1.0
	set now [$ns now]
	set bw1 [$sink1 set bytes_]
	set bw2 [$sink2 set bytes_]

	if { $Scenario_No == 2} {
	set bw3 [$sink3 set bytes_]
	puts $f2 "$now [expr $bw3/$time*8/1000]"
	}


	
	puts $f0 "$now [expr $bw1/$time*8/1000]"
	puts $f1 "$now [expr $bw2/$time*8/1000]"
	
		
	#neglecting the first 100 sec
	if {$now>30 && $now<=180} {
		
		set throughput1 [expr $throughput1+$bw1/$time*8/1000]
		set throughput2 [expr $throughput2+$bw2/$time*8/1000]
	

	
if { $Scenario_No == 2} {
	
	set throughput3 [expr $throughput3+$bw3/$time*8/1000]
	
	}
	}
	
	if {$now == 180} {
		puts "Average Throughput for Src1 is = [expr $throughput1*$time/150] Kbps \n"
		puts "Average Throughput for Src2 is = [expr $throughput2*$time/150] Kbps \n"
	if {$Scenario_No == 2} {
		puts "Average Throughput for Src3 is = [expr $throughput3*$time/150] Kbps \n"
	}
	}
	#Reset the bytes to 0
	$sink1 set bytes_ 0
	$sink2 set bytes_ 0
	if { $Scenario_No == 2 } {
$sink3 set bytes_ 0
}
	#Reschedule
	$ns at [expr $now+$time] "record"
}

#Start nam
proc finish {} {
global ns nf f0 f1 f2 throughput1 throughput2 throughtput3 Scenario_No Mechanism
$ns flush-trace
close $nf
close $f0
close $f1

puts "Opening NAM"
exec nam tcp.nam &
if { $Scenario_No == 1} {
exec xgraph th1.tr th2.tr -geometry 800x400 & 
}
if { $Scenario_No == 2} {
close $f2
exec xgraph th1.tr th2.tr th3.tr -geometry 800x400 & 
}
exit 0
}

#Timing the ns commands
$ns at 0 "record"
$ns at 0 "$ftp1 start"
$ns at 0 "$ftp2 start"
if { $Scenario_No == 2} {
$ns at 0 "$cbr_1 start"
$ns at 180 "$cbr_1 stop"
}
$ns at 181 "$ftp1 stop"
$ns at 181 "$ftp2 stop"
$ns at 181 "finish"

$ns run
