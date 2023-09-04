def writeHeader():
    outstr = \
        '''<?xml version="1.0"?>
    <!DOCTYPE network SYSTEM "network.dtd">
    <network locale="C" version="1.7" reference_time="13:28:25.000 Dec 18 2010" attribute_processing="explicit">
    <subnet name="Campus Network">
    '''
    return outstr


def writeFeeter():
    outstr = \
        '''        <attr name="priority" value="0"/>
    <attr name="user id" value="0"/>
    <attr name="x position" value="0.0"/>
    <attr name="y position" value="0.0"/>
    <attr name="icon name" value="subnet"/>
    <attr name="outline color" value="blue"/>
    <attr name="doc file" value="nt_fixed_subnet"/>
    <attr name="creation source" value="Object Palette"/>
    <attr name="creation timestamp" value="13:21:18 Dec 18 2010"/>
    <attr name="creation data" value=""/>
    <characteristic name="units" value="Kilometers"/>
    </subnet>
    </network>
    '''
    return outstr


def writeRXGroup(x, y, commrange):
    outstr =\
        '''        <node name="RXGroup" model="MWSReceiverGroup" ignore_questions="true" min_match_score="strict matching">
    <attr name="x position" value="'''+str(x)+'''"/>
    <attr name="y position" value="'''+str(y)+'''"/>
    <attr name="threshold" value="0.0"/>
    <attr name="icon name" value="util_rxgroup"/>
    <attr name="doc file" value="nt_fixed_node"/>
    <attr name="tooltip" value="Receiver Group Configuration"/>
    <attr name="creation source" value="Object copy"/>
    <attr name="creation timestamp" value="13:24:05 Dec 18 2010"/>
    <attr name="creation data" value=""/>
    <attr name="label color" value="black"/>
    <attr name="drgm.Use Connection File" value="enabled"/>
    <attr name="Distance Threshold (meters)" value="'''+str(commrange)+'''" symbolic="true"/>
    </node>
    '''
    return outstr


def writeSeverNode(x, y):
    outstr =\
        '''        <node name="Scheduler Sever" model="CentralSever" ignore_questions="true" min_match_score="strict matching">
    <attr name="x position" value="'''+str(x)+'''"/>
    <attr name="y position" value="'''+str(y)+'''"/>
    <attr name="icon name" value="server"/>
    <attr name="doc file" value=""/>
    <attr name="tooltip" value=""/>
    <attr name="creation source" value="Object Palette"/>
    <attr name="creation timestamp" value="13:45:17 Dec 18 2010"/>
    <attr name="creation data" value=""/>
    </node>
    '''
    return outstr


def writeMNNode(x, y, node_ip, flow_dst_ip, startTime, stopTime, pktSize, intervalStr='constant (0.015)'):
    outstr =\
        '''        <node name="node_'''+str(node_ip)+'''" model="MWSCentralMN" ignore_questions="true" min_match_score="strict matching">
    <attr name="x position" value="'''+str(x)+'''"/>
    <attr name="y position" value="'''+str(y)+'''"/>
    <attr name="threshold" value="0.0"/>
    <attr name="icon name" value="armoured_jeep.chassis"/>
    <attr name="doc file" value=""/>
    <attr name="tooltip" value=""/>
    <attr name="creation source" value="Object Palette"/>
    <attr name="creation timestamp" value="13:42:43 Dec 18 2010"/>
    <attr name="creation data" value=""/>
    <attr name="label color" value="black"/>
    <attr name="flow_dst_ip" value="'''+str(flow_dst_ip)+'''"/>
    <attr name="node_ip" value="'''+str(node_ip)+'''"/>
    <attr name="traffic_gen.Packet Interarrival Time" value="'''+intervalStr+'''"/>
    <attr name="traffic_gen.Packet Size" value="constant ('''+str(pktSize)+''')"/>
    <attr name="traffic_gen.Start Time" value="'''+str(startTime)+'''"/>
    <attr name="traffic_gen.Stop Time" value="'''+str(stopTime)+'''"/>
    </node>
    '''
    return outstr


if __name__ == '__main__':
    file = ''
    file += writeHeader()
    file += writeRXGroup(0, 0, 1000)
    file += writeSeverNode(1, 1)
    file += writeMNNode(5.02, 6.03, 3, 0, 10.1, 20, 20)
    file += writeFeeter()
    print(file)

    # 写入文件
    f = open('opnet-demo.xml', 'w')
    f.write(file)
    f.close()
