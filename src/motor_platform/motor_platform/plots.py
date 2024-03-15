def scatter_attribute(list, attribute: str, ax):
    time_list = [datum.header.timestamp.microseconds for datum in list]
    attribute_list = [getattr(datum, attribute) for datum in list]

    ax.scatter(time_list, attribute_list, label=attribute)
