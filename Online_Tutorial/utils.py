import h5py as h5
from obspy.core import UTCDateTime as udt

def load_data(filename, path='./'):
    data = {}
    with h5.File(path + filename, mode='r') as f:
        data['metadata'] = {}
        data['metadata']['stations'] = f['stations'][()].astype('U').tolist()
        data['metadata']['components'] = f['components'][()].astype('U').tolist()
        data['metadata']['date'] = udt(f['date'][()])
        data['metadata']['sampling_rate'] = f['sampling_rate'][()]
        data['waveforms'] = f['waveforms'][()]
    return data

def load_template(filename, path='./'):
    template = {}
    with h5.File(path + filename, mode='r') as f:
        for key in f.keys():
            template[key] = f[key][()]
    return template

def load_cc(filename, path='./output/'):
    with h5.File(path + filename, mode='r') as f:
        cc_sum = f['cc_sum'][()]
    return cc_sum

def load_detections(filename, tid, path='./output/'):
    meta = filename + 'meta.h5'
    wav = filename + 'wav.h5'
    detections = {}
    with h5.File(path + meta, mode='r') as f:
        detections['metadata'] = {}
        for key in f[str(tid)].keys():
            detections['metadata'][key] = f[str(tid)][key][()]
    with h5.File(path + wav, mode='r') as f:
        detections['waveforms'] = f[str(tid)]['waveforms'][()]
    detections['metadata']['stations'] = detections['metadata']['stations'].astype('U')
    detections['metadata']['components'] = detections['metadata']['components'].astype('U')
    return detections
