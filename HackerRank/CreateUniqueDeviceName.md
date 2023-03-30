
Object:
Given a array of device names (strings) which contains duplicate names. The aim is to create an array of unique device names. If there are more than one same device names, counting from 0, the 1st one will be appended with '1', the 2nd one will be appended with '2', ...

```
devices = ['switch', 'tv, 'switch', 'tv, 'switch', 'tv']

def nameDevices(deviceList):
    uniqueDevices = []  # Empty list to store unique name
    for i, device in enumerate(deviceList):
        occur = deviceList[:i].count(device)    # Count the occurence of the device in deviceList[0:i] sublist
        if (occur > 0):
            uniqueDevices.append(device + str(occur))   # Add 'devicename'+'occur'
        else:
            uniqueDevices.append(device)    # Add 'devicename' only
    
    return uniqueDevices

uDevices = nameDevices(devices)
print(uDevices)
['switch', 'tv', 'switch1', 'tv1', 'switch2', 'tv2']
```

The solution is taken from [stackoverflow](https://stackoverflow.com/questions/62929107/creating-unique-device-names)