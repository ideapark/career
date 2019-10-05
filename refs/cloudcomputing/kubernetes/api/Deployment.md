# Deployment

Declarative definition for Pod and ReplicaSet, also as a replacement of
ReplicationController.

# Usage

- Creating Pod & ReplicaSet
- Rolling update or rollout
- Scale up or down
- Pause or resume Deployment

kubectl scale deployment nginx-deployment --replicas 10
kubectl autoscale deployment nginx-deployment --min=10 --max=15 --cpu-percent=80
kubectl set image deployment/nginx-deployment nginx=nginx:1.9.1
kubectl rollout undo deployment/nginx-deployment
