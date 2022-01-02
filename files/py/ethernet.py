import threading as thread
from time import *
from random import *

MAXMAC = 281474976710655
MAXWAIT = 10 * 3

machines = []

class Machine:
  def __init__(self, mac, domain):
    self.mac = mac
    self.domain = domain


  def send_to_domain(self, domain, machine):
    ret = 0
    for m in domain.machines:
      if m == self:
        continue
      print(f"  {self.mac} on domain {self.domain.id} to {m.mac} on domain {m.domain.id}")
      if m == machine:
        machine.receive(self)
        ret = 1
    return ret

  def send(self, machine):
    print(f"MESSAGE FOR {machine.mac} ON DOMAIN {machine.domain.id}")
    ret = 0

    # Send to all on local domain
    ret = self.send_to_domain(self.domain, machine)

    # Query switch(es) if necessary to send to outside domains
    if machine.domain.id != self.domain.id:
      for switch in self.domain.switches:
        if machine in switch.machines and machine.domain.id != self.domain.id:
          print(f"  SWITCH to domain {machine.domain.id} contains MAC")
          ret = self.send_to_domain(machine.domain, machine)
          break


    if ret == 0:
      print(f"MESSAGE FAILED TO DELIVER")
    else:
      print("MESSAGE SUCCESSFUL")
    print()

  def listen(self):
    while(True):
      sleep(randint(0, MAXWAIT) * 0.10)
      machine = self
      while (machine == self):
        index = randint(0, len(machines))
        machine = machines[i]
      self.send(machine)

  def receive(self, machine):
    print(f"    {self.mac} on domain {self.domain.id} from {machine.mac} on domain {machine.domain.id}")


class Domain:
  def __init__(self):
    self.machines = []
    self.num_machines = 0
    self.switches = []
    self.id = -1

  def add(self, machine):
    self.machines.append(machine)
    self.num_machines += 1


class Switch:
  machines = []

  def __init__(self, domains):
    self.domains = domains
    for domain in domains:
      domain.switches.append(self)
      for m in domain.machines:
        self.machines.append(m)

ndomains = 2
threads= []
domains = []

for i in range(ndomains):
  d = Domain()
  d.id = i
  for j in range(3):
    m = Machine(randint(0, MAXMAC), d)
    d.add(m)
    machines.append(m)
    threads.append(thread.Thread(target=m.listen, args=()))
  domains.append(d)

s = Switch(domains) 

for thread in threads:
  thread.start()
