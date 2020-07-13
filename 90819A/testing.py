def curvature(lookahead):
    global path, pos, angle
    side = np.sign(math.sin(3.1415/2 - angle)*(lookahead[0]-pos[0]) - math.cos(3.1415/2 - angle)*(lookahead[1]-pos[1]))
    a = -math.tan(3.1415/2 - angle)
    c = math.tan(3.1415/2 - angle)*pos[0] - pos[1]
    # x = abs(-math.tan(3.1415/2 - angle) * lookahead[0] + lookahead[1] + math.tan(3.1415/2 - angle)*pos[0] - pos[1]) / math.sqrt((math.tan(3.1415/2 - angle))**2 + 1)
    x = abs(a*lookahead[0] + lookahead[1] + c) / math.sqrt(a**2 + 1)
    return side * (2*x/(float(config["PATH"]["LOOKAHEAD"])**2))

curvature([0, 0])